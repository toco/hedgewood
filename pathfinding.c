/*X 1)  	Füge das Startquadrat der offenen Liste hinzu.
	2)  	Wiederhole das Folgende:
	X	a) 	Suche in der offenen Liste nach dem Quadrat mit dem niedrigsten F-Wert. Wir bezeichnen dieses Quadrat im Folgenden als das aktuelle Quadrat.
	X	b) 	Verschiebe es in die geschlossene Liste.
		c) 	Für jedes der 8 an das aktuelle Quadrat angrenzenden Quadrate:
		* Wenn es nicht begehbar ist oder sich bereits in der geschlossenen Liste befindet, ignoriere es; andernfalls mach das Folgende:
		* Wenn es nicht in der offenen Liste ist, füge es der offenen Liste hinzu. Trage das aktuelle Quadrat als Vorgängerquadrat dieses Quadrats ein. Trage zusätzlich die Werte für die F-, G- und H-Kosten dieses Quadrates ein.
		* Falls es bereits in der offenen Liste ist, prüfe, ob der Pfad vom aktuellen Quadrat zu ihm - gemessen am G-Wert -, besser ist, als der Pfad von seinem eingetragenen Vorgängerquadrat (ein geringerer G-Wert bedeutet einen besseren Pfad). Falls dem so ist, ändere sein Vorgängerquadrat auf das aktuelle Quadrat und berechne seine Werte für G und F neu. Sofern Du Deine offene Liste nach dem F-Wert sortiert hast, ist möglicherweise eine Neusortierung dieser Liste erforderlich, um dieser Veränderung Rechnung zu tragen.
		d) 	Beende den Prozess, falls:
		* Du das Zielquadrat in die geschlossene Liste verschoben hast; in diesem Fall hast Du den Pfad ermittelt
		* kein Zielquadrat gefunden werden konnte und die offene Liste leer ist; in diesem Fall gibt es keinen Pfad.
	3)  Sichere den Pfad. Der Pfad erschließt sich, indem Du vom Zielquadrat aus Quadrat für Quadrat rückwärts schreitend das Startquadrat erreichst.
	 *
		Der Schlüssel dazu, welche Quadrate für den Pfad in Frage kommen, ist folgende Gleichung:
		F = G + H
		wobei
		* G = Die Bewegungskosten, um vom Startpunkt A zu einem gegebenen Quadrat des Gitters unter Verwendung des dafür ermittelten Pfades zu gelangen.
		* H = Die geschätzten Kosten, um von dem gegebenen Quadrat zum Zielpunkt B zu gelangen. Dies wird oft heuristisch genannt, was ein bisschen verwirrend sein kann. Der Grund, warum dies so genannt wird, ist, dass diese Kosten auf Vermutung beruhen, denn tatsächlich kennen wir die wirkliche Entfernung erst, wenn wir den Pfad dorthin gefunden und auf dem Weg liegende Hindernisse (Wände, Wasser, etc.) berücksichtigt haben. In diesem Artikel wird ein möglicher Weg gezeigt, wie H ermittelt werden kann; es gibt aber viele weitere, die in anderen Web-Artikeln beschrieben sind.
*/
#include "SDLincludes.h"
#include "SDLfunctions.h"
#include "pathfinding.h"

void aStar( dataStore *data, position *end) {
	if(end==NULL || data->hedgewood[end->y][end->x].aStarValue<0)return;
	else {
		int suchen=1,i,j,aStarVal;
		pfNode *open=NULL,*closed=NULL,*zeiger=NULL,*tmp_element=NULL;
		position start = data->player.p_pos;
		
		positionListDelete(data);
		
		position tmp_pos[4];
		
		if ((zeiger = calloc(1,sizeof(struct pfNode)))==NULL) {
			printf("MEM::pathfinding::35");
			return;
		}
		zeiger->n_pos=start;
		open=zeiger;
		while(suchen) {
			zeiger=aStarSearchF(open);
			if(DBPATH)printf("NEWTESTField x:%d y:%d G:%d H:%d F:%d\n",zeiger->n_pos.x,zeiger->n_pos.y,zeiger->G,zeiger->H,zeiger->F);
			if(DEBUG)printf("tmp 58 x: %d y: %d\n",zeiger->n_pos.x,zeiger->n_pos.y);
			open=aStarListRemove(open,zeiger,pfNode_list);
			closed=aStarListAdd(closed,zeiger,pfNode_list);
			if(DEBUG)printf("closed 61 x: %d y: %d\n",closed->n_pos.x,closed->n_pos.y);
			for(i=-1; i<2; i=i+2) {
				tmp_pos[i+1].x=zeiger->n_pos.x;
				tmp_pos[i+1].y=zeiger->n_pos.y+i;
				tmp_pos[i+2].x=zeiger->n_pos.x-i;
				tmp_pos[i+2].y=zeiger->n_pos.y;
				tmp_pos[i+1].next=NULL;
				tmp_pos[i+2].next=NULL;
				if(tmp_pos[i+1].y<0)tmp_pos[i+1].y=0;
				if(tmp_pos[i+1].y>(FIELDSIZE_Y-1))tmp_pos[i+1].y=(FIELDSIZE_Y-1);
				if(tmp_pos[i+2].x>(FIELDSIZE_X-1))tmp_pos[i+2].x=(FIELDSIZE_X-1);
				if(tmp_pos[i+2].x<0)tmp_pos[i+2].x=0;
			}
			for(i=0; i<4; i++) {
				if ((tmp_element = calloc(1,sizeof(struct pfNode)))==NULL) {
					printf("MEM::pathfinding::81");
					return;
				}
				tmp_element->n_pos=tmp_pos[i] ;
				if(data->hedgewood[tmp_pos[i].y][tmp_pos[i].x].visible==1)aStarVal=(data->hedgewood[tmp_pos[i].y][tmp_pos[i].x].aStarValue);
				else aStarVal=AVGASTAR*3;
				if((aStarListSearchBool(closed,tmp_element)==NULL) &&  !(aStarVal<0)) {
					if(aStarListSearchBool(open,tmp_element)==NULL) {
						tmp_element->last=zeiger;
						tmp_element->G=tmp_element->last->G+aStarVal;
						tmp_element->H=aStarManhatten(tmp_element->n_pos,*end);
						tmp_element->F=tmp_element->G+tmp_element->H;
						open=aStarListAdd(open,tmp_element,pfNode_list);
					} else {
						tmp_element = aStarListSearchBool(open,tmp_element);
						j=zeiger->G+aStarVal;
						if(tmp_element->G > j) {
							tmp_element->G = j;
							tmp_element->F=tmp_element->G+tmp_element->H;
							tmp_element->last=zeiger;
						}
					}
					if(DBPATH)printf("Field x:%d y:%d G:%d H:%d F:%d\n",tmp_element->n_pos.x,tmp_element->n_pos.y,tmp_element->G,tmp_element->H,tmp_element->F);
				} else {
					if(DBPATH)printf("Field x:%d y:%d G:%d H:%d F:%d IGNORE\n",tmp_element->n_pos.x,tmp_element->n_pos.y,tmp_element->G,tmp_element->H,tmp_element->F);
					free(tmp_element);
				}
			}
			if(aStarManhatten(zeiger->n_pos,*end)==0) {
				suchen=0;
				while(zeiger->last!=NULL) {
					positionListAdd(data,&zeiger->n_pos);
					zeiger=zeiger->last;
				}
				aStarListDelete(open);
				return;
			}
		}
	}
}

//Fuegt hinten an die Liste das Element pos_add an.
void positionListAdd(dataStore *data,  position *pos_add) {
	struct position *zeiger=NULL;
	pos_add->next=NULL;
	if(data->player.anfang == NULL) {
		data->player.anfang=pos_add;
		data->player.anfang->next=NULL;
		if(DEBUG)printf("Position next first x: %d y: %d\n",data->player.anfang->x,data->player.anfang->y);
	} else {
		if(DEBUG)printf("Position to add before x: %d y: %d\n",pos_add->x,pos_add->y);		
		zeiger=data->player.anfang;
		data->player.anfang=pos_add;
		data->player.anfang->next=zeiger;
	}
	if(DEBUG)printf("Position Start x: %d y: %d\n",data->player.anfang->x,data->player.anfang->y);
}

void positionListDelete( dataStore *data) {
	struct position *zeiger, *zeiger1;
	if(data->player.anfang != NULL) {
		zeiger=data->player.anfang->next;
		while(zeiger != NULL) {
			zeiger1=zeiger->next;
			free(zeiger);
			zeiger=zeiger1;
		}
		data->player.anfang=NULL;
	}
}

//liest die obere Position des Stacks und entfernt diesen
position *positionListRead( dataStore *data) {
	printdb("Start ListRead\n");
	struct position *result;
	if(data->player.anfang==NULL) {
		printf("Die Liste ist Leer\n");
		return NULL;
	} else {
		if(DEBUG)printf("Position read x: %d y: %d\n",data->player.anfang->x,data->player.anfang->y);
		result=data->player.anfang;
		data->player.anfang=data->player.anfang->next;
	}
	printdb("END ListRead\n");
	if(DEBUG)if(data->player.anfang!=NULL)printf("Position read end x: %d y: %d\n",data->player.anfang->x,data->player.anfang->y);
	return result;
}

//stack==1 -> list
//stack==2 -> last
pfNode *aStarListAdd(pfNode *list,pfNode *node_add, int stack) {
	if(stack==pfNode_list) {
		if(list == NULL) {
			list=node_add;
			if(DEBUG)printf("Node added to list x: %d y: %d\n",list->n_pos.x,list->n_pos.y);
			return list;
		} else {
			node_add->list=list;
			if(DEBUG)printf("Node added to list x: %d y: %d\n",node_add->n_pos.x,node_add->n_pos.y);
			return node_add;
		}
	} else if(stack==pfNode_last) {
		if(list == NULL) {
			list=node_add;
			list->last=NULL;
			if(DEBUG)printf("Node added to list x: %d y: %d\n",list->n_pos.x,list->n_pos.y);
			return list;
		} else {
			node_add->last=list;
			if(DEBUG)printf("Node added to list x: %d y: %d\n",node_add->n_pos.x,node_add->n_pos.y);
			return node_add;
		}
	}
	return list;
}

//sucht den kleinsten F-Wert (erster Fund wird Ausgegeben)
pfNode *aStarSearchF(pfNode *list) {
	pfNode *result=list,*tmp=list;
	while(tmp!=NULL) {
		if(tmp->F<result->F) {
			result=tmp;
			if(DEBUG)printf("min Element x: %d y: %d\n",result->n_pos.x,result->n_pos.y);
		}
		tmp=tmp->list;
	}
	return result;
}

pfNode *aStarListSearchBool(pfNode *list,pfNode *element) {
	pfNode *tmp=list;
	while(tmp!=NULL) {
		if(tmp->n_pos.x != element->n_pos.x || tmp->n_pos.y != element->n_pos.y) {
			tmp=tmp->list;
		} else return tmp;
	}
	return NULL;
}

int aStarManhatten(position start, position end) {
	int x=0,y=0;
	x=end.x-start.x;
	y=end.y-start.y;
	if(x<0)x*=(-1);
	if(y<0)y*=(-1);
	return ((x+y)*AVGASTAR);
}

pfNode *aStarListRemove(pfNode *list,pfNode *node_remove, int stack) {
	pfNode *tmp=list,*tmp2=NULL;
	if(tmp!=NULL) {
		if(stack==pfNode_list) {
			if(tmp->n_pos.x == node_remove->n_pos.x && tmp->n_pos.y == node_remove->n_pos.y) {
				list=list->list;
				return list;
			} else {
				if(tmp->list!=NULL) {
					while(tmp->list!=NULL) {
						if(tmp->list->n_pos.x != node_remove->n_pos.x || tmp->list->n_pos.y != node_remove->n_pos.y) {
							tmp=tmp->list;
						} else {
							tmp2=tmp->list->list;
							tmp->list->list=NULL;
							tmp->list=tmp2;
							return list;
						}
					}
				} else {
					if(tmp->n_pos.x == node_remove->n_pos.x && tmp->n_pos.y == node_remove->n_pos.y) {
						list=NULL;
						return list;
					}
				}
			}
		}
	}
	return list;
}

void aStarListDelete(pfNode *list) {
	struct pfNode *zeiger, *zeiger1;
	if(list != NULL) {
		zeiger=list->list;
		while(zeiger != NULL) {
			zeiger1=zeiger->list;
			free(zeiger);
			zeiger=zeiger1;
		}
		free(list);
	}
}
