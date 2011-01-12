#include "SDLincludes.h"
#include "SDLfunctions.h"


#include "pathfinding.h"

void aStar(struct dataStore *data,struct position *end){
	
	int suchen=0;
	pfNode *open=NULL; 
	pfNode *closed=NULL ;
	
	struct position start = data->player.p_pos;
	
	if ((open = realloc(open,sizeof(struct pfNode)))==NULL) {
		printf("MEM::pathfinding::15");
		return;
	}
	
	open[0].n_pos=start;
	open[0].F=0;
	open[0].G=0;
	open[0].H=0;
	open[0].last=NULL;
	
	while(suchen){
		
	}
	
}

//Fuegt hinten an die Liste das Element pos_add an.
void positionListAdd(struct dataStore *data, struct position *pos_add) {
       
	struct position *zeiger=NULL;
	
	if(data->player.anfang == NULL) {
	
		if((data->player.anfang =calloc(1,sizeof(struct position))) == NULL) {
			printf("Kein Speicherplatz vorhanden fuer position\n");
			return;
		}
		if((data->player.next =calloc(1,sizeof(struct position))) == NULL) {
			printf("Kein Speicherplatz vorhanden fuer position\n");
			return;
		}
		memcpy(data->player.anfang,pos_add,sizeof(struct position));
		data->player.anfang->next=NULL;
		data->player.next=data->player.anfang;
		if(DEBUG)printf("Position next first x: %d y: %d\n",data->player.next->x,data->player.next->y);
	}	
	else {
		if(DEBUG)printf("Position to add before x: %d y: %d\n",pos_add->x,pos_add->y);
		if((zeiger=calloc(1,sizeof(struct position))) == NULL) {
			printf("Kein Speicherplatz vorhanden fuer position\n");
			return;
		}
		
		if((data->player.next->next =calloc(1,sizeof(struct position))) == NULL) {
			printf("MEM::pathfinding::42\n");
			return;
		}
		memcpy(data->player.next->next,pos_add,sizeof(struct position));
		if(DEBUG)printf("data->player.next x: %d y: %d\n",data->player.next->x,data->player.next->y);
		if(DEBUG)printf("data->player.next->next x: %d y: %d\n",data->player.next->next->x,data->player.next->next->y);
		data->player.next = data->player.next->next;
		data->player.next->next=NULL;
		
		free(zeiger);
		
	}
	printf("Position added x: %d y: %d\n",data->player.next->x,data->player.next->y);
	printf("Position Start x: %d y: %d\n",data->player.anfang->x,data->player.anfang->y);
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
				free(data->player.next);
                data->player.anfang=NULL;
				data->player.next=NULL;
        }
}

//liest die obere Position des Stacks und entfernt diesen
struct position *positionListRead(struct dataStore *data) {
		printdb("Start ListRead\n");
		
        struct position *result,*tmp;
		
		if(data->player.anfang==NULL){
			printf("Die Liste ist Leer\n");
			return NULL;
		}
		else{
			if(DEBUG)printf("Position read x: %d y: %d\n",data->player.anfang->x,data->player.anfang->y);
		if((result =calloc(1,sizeof(struct position))) == NULL) {
			printf("MEM::pathfinding::42\n");
			return NULL;
		}
		if((tmp =calloc(1,sizeof(struct position))) == NULL) {
			printf("MEM::pathfinding::42\n");
			return NULL;
		}
			memcpy(result,data->player.anfang,sizeof(struct position));
			tmp=data->player.anfang->next;
			free(data->player.anfang);
			data->player.anfang=tmp;
			//free(tmp);

        }
		printdb("END ListRead\n");
		if(DEBUG)if(data->player.anfang!=NULL)printf("Position read end x: %d y: %d\n",data->player.anfang->x,data->player.anfang->y);
		return result;
		
		
}