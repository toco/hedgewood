/*X 1)  	Füge das Startquadrat der offenen Liste hinzu.
	2)  	Wiederhole das Folgende:
	X	a) 	Suche in der offenen Liste nach dem Quadrat mit dem niedrigsten F-Wert. Wir bezeichnen dieses Quadrat im Folgenden als das aktuelle Quadrat.
		b) 	Verschiebe es in die geschlossene Liste.
		c) 	Für jedes der 8 an das aktuelle Quadrat angrenzenden Quadrate:


		* Wenn es nicht begehbar ist oder sich bereits in der geschlossenen Liste befindet, ignoriere es; andernfalls mach das Folgende:
		* Wenn es nicht in der offenen Liste ist, füge es der offenen Liste hinzu. Trage das aktuelle Quadrat als Vorgängerquadrat dieses Quadrats ein. Trage zusätzlich die Werte für die F-, G- und H-Kosten dieses Quadrates ein.
		* Falls es bereits in der offenen Liste ist, prüfe, ob der Pfad vom aktuellen Quadrat zu ihm - gemessen am G-Wert -, besser ist, als der Pfad von seinem eingetragenen Vorgängerquadrat (ein geringerer G-Wert bedeutet einen besseren Pfad). Falls dem so ist, ändere sein Vorgängerquadrat auf das aktuelle Quadrat und berechne seine Werte für G und F neu. Sofern Du Deine offene Liste nach dem F-Wert sortiert hast, ist möglicherweise eine Neusortierung dieser Liste erforderlich, um dieser Veränderung Rechnung zu tragen.

		d) 	Beende den Prozess, falls:

		* Du das Zielquadrat in die geschlossene Liste verschoben hast; in diesem Fall hast Du den Pfad ermittelt
		* kein Zielquadrat gefunden werden konnte und die offene Liste leer ist; in diesem Fall gibt es keinen Pfad.

	3)  Sichere den Pfad. Der Pfad erschließt sich, indem Du vom Zielquadrat aus Quadrat für Quadrat rückwärts schreitend das Startquadrat erreichst.
*/

#include "SDLincludes.h"
#include "SDLfunctions.h"
#include "pathfinding.h"

void aStar(struct dataStore *data,struct position *end) {

	int suchen=1,i,open_length,f_min;
	pfNode *open=NULL;
	pfNode *closed=NULL ;
	pfNode *zeiger=NULL;
	pfNode *tmp=NULL;

	struct position start = data->player.p_pos;

	if ((zeiger = calloc(1,sizeof(struct pfNode)))==NULL) {
		printf("MEM::pathfinding::35");
		return;
	}

	zeiger->n_pos=start;
	zeiger->F=0;
	zeiger->G=0;
	zeiger->H=0;
	zeiger->last=NULL;
	zeiger->list=NULL;
	open=zeiger;

	while(suchen) {
		//sucht den kleinsten F-Wert (erster Fund wird Ausgegeben)
		tmp=open;
		zeiger=open;
		while(tmp->list!=NULL) {
			if(tmp->list->F < tmp->F )zeiger=tmp;
			tmp=tmp->list;
		}
		tmp=zeiger->list;
		zeiger->list=zeiger->list->list;
		
		if(closed == NULL) {

			if((closed =calloc(1,sizeof(struct pfNode))) == NULL) {
				printf("MEM::pathfinding::58");
				return;
			}
			closed = tmp;
			closed->list=NULL;
			if(DBPATH)printf("Position next first x: %d y: %d\n",data->player.next->x,data->player.next->y);
		} else {
			zeiger= closed;
			if((tmp->list=calloc(1,sizeof(struct pfNode))) == NULL) {
				printf("MEM::pathfinding::67");
				return;
			}
			closed=tmp;
			closed->list=zeiger;

			free(zeiger);
			free(tmp);
		}
		

	}
	suchen=0;

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
	} else {
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

	if(data->player.anfang==NULL) {
		printf("Die Liste ist Leer\n");
		return NULL;
	} else {
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
