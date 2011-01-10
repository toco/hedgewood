#include "pathfinding.h"

//void aStar(struct dataStore *data,struct position *end)
	



//Fuegt hinten an die Liste das Element pos_add an.
void positionListAdd(struct dataStore *data, struct position *pos_add) {
       
	struct position *zeiger;

	if(data->player.anfang == NULL) {
	
		if((data->player.anfang =malloc(sizeof(struct position))) == NULL) {
			printf("Kein Speicherplatz vorhanden fuer position\n");
			return;
		}
		data->player.anfang=pos_add;
		data->player.anfang->next=NULL;
	}	
	else {
		if((zeiger=malloc(sizeof(struct position))) == NULL) {
			printf("Kein Speicherplatz vorhanden fuer position\n");
			return;
		}
		zeiger=data->player.anfang; 
		if(pos_add== NULL) {
			printf("Input ist NULL\n");
            return;
		}
		data->player.anfang=pos_add;
		data->player.anfang->next=zeiger;
		free(zeiger);
		//free(pos_add);                
	}
}

void positionListDelete(struct dataStore *data) {
        struct position *zeiger, *zeiger1;

        if(data->player.anfang != NULL) {
			
                zeiger=data->player.anfang->next;
				while(zeiger != NULL) {
					zeiger1=zeiger->next;
					free(zeiger);
					zeiger=zeiger1;
                }
                free(data->player.anfang);
                data->player.anfang=NULL;
        }
}

//liest die obere Position des Stacks und entfernt diesen
struct position *positionListRead(struct dataStore *data) {
		
        struct position *result,*tmp;
		
		if(data->player.anfang==NULL){
			printf("Die Liste ist Leer\n");
			return NULL;
		}
		//else if(data->player.anfang->next==NULL) {
		//	return data->player.anfang;
		//}			
		else{
			if((tmp=malloc(sizeof(struct position))) == NULL) {
			printf("Kein Speicherplatz vorhanden fuer position\n");
			return;
			}
			result=data->player.anfang;
			tmp=data->player.anfang->next;
			//free(data->player.anfang);
			data->player.anfang=tmp;
			//free(tmp);
			//data->player.anfang=data->player.anfang->next;
        }
		
		return result;
}