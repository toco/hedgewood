#include "SDLincludes.h"
#include "graphicUpdate.h"
#define field_pic "./pictures/textur.png"
#define start_pic "./pictures/startzonetest.png"
#define person_pic "./pictures/person_iso.png"
#define kreis_pic "./pictures/kreis.png"
#define candy_pic "./pictures/zuckerstangen.png"
#define animation_pic "./pictures/cutanimation.png"
/**Zeichnet das aktuell sichtbare Spielfeld mit der Person.	* 
	* @param l_screen an SDL_Surface.
	* @param data a dataStore pointer.
	* @see dataStore
	* @return 1 if successful
	* @return 0 if fail
*/
int GraphicUpdate(SDL_Surface *l_screen,dataStore *data)
{
	int i,j,scrollposition=data->verticalScroll,hSpos=data->horizontalScroll,startzone=0;
	float energy;
	SDL_Surface *image_start=NULL,*image_field=NULL,*image_person=NULL,*image_candy=NULL;
	SDL_Rect src, dst, src2;
	if ((image_start =load_image(start_pic))== NULL) {
		printf("Can't load image start: %s\n", SDL_GetError());
		exit(1);
	}
	if ((image_field=load_image(field_pic)) == NULL) {
		printf("Can't load image field: %s\n", SDL_GetError());
		exit(1);
	}
	if ((image_person=load_image(person_pic)) == NULL) {
		printf("Can't load image person: %s\n", SDL_GetError());
		exit(1);
	}
	if ((image_candy=load_image(candy_pic)) == NULL) {
		printf("Can't load image person: %s\n", SDL_GetError());
		exit(1);
	}
	dst.h = src.h = 70;
	dst.w = src.w = FIELDSIZE_FIELD;
	for(j=0; j<12; j++) {
		if(j==0)dst.y = 0;
		else dst.y = FIELDSIZE_FIELD*j-20;
		for(i=0; i<16; i++) {
			if(data->hedgewood[j+scrollposition][i+hSpos].type==-1)startzone=1;
			else startzone=0;
			dst.x = FIELDSIZE_FIELD*i;
			if(startzone) {
				dst.y = FIELDSIZE_FIELD*j;
				src.x = FIELDSIZE_FIELD*(i+hSpos);
				src.y = FIELDSIZE_FIELD*(j+scrollposition);
			} else {
				src.x = FIELDSIZE_FIELD*data->hedgewood[j+scrollposition][i+hSpos].type*data->hedgewood[j+scrollposition][i+hSpos].visible;
				if(j==0) {
					src.y = 20;
					dst.h = src.h = 50;
				} else {
					dst.y = FIELDSIZE_FIELD*j-20;
					src.y = 0;
					dst.h = src.h = 70;
				}
			}
			if(startzone)SDL_BlitSurface(image_start, &src, l_screen, &dst);
			else {/**<print candy*/
				SDL_BlitSurface(image_field, &src, l_screen, &dst);
				
				if(data->hedgewood[j+scrollposition][i+hSpos].currency > 0 && src.x>0) {
					src2=src;
					src2.x=50*((data->hedgewood[j+scrollposition][i+hSpos].currency-1)/10);
					if(src2.x>100)src2.x=100;
					SDL_BlitSurface(image_candy, &src2, l_screen, &dst);
				}
			}
			
			if(data->player.p_pos.x==i+hSpos && data->player.p_pos.y==j+scrollposition) {/**<print person*/
				src.x = FIELDSIZE_FIELD*data->player.heading;
				src.y = 0;
				dst.x = FIELDSIZE_FIELD*(data->player.p_pos.x-hSpos);
				dst.y = FIELDSIZE_FIELD*(data->player.p_pos.y-scrollposition)-20;
				src.h = dst.h = 70;
				SDL_BlitSurface(image_person, &src, l_screen, &dst);
			}
		}
	}
	SDL_FreeSurface(image_start);
	SDL_FreeSurface(image_field);
	SDL_FreeSurface(image_candy);
	aStarPathPrint(data,l_screen);
	/**<print energy bar*/
	src.x= 25;
	dst.x = 23;
	src.y=25;
	dst.y = 23;
	dst.w = 204;
	src.h=25;
	dst.h = 29;
	energy=200*(((float)data->player.currentEnergy)/((float)data->player.maxEnergy));
	src.w = energy;
	SDL_FillRect(l_screen, &dst, SDL_MapRGBA( l_screen->format, 0,0, 0,255));
	dst.x = 573;
	SDL_FillRect(l_screen, &dst, SDL_MapRGBA( l_screen->format, 0,0, 0,255));
	dst.x = 25;
	dst.y += 2;
	dst.w -= 4;
	dst.h -= 4;
	SDL_FillRect(l_screen, &dst, SDL_MapRGBA( l_screen->format, 255, 115, 0,255));
	SDL_FillRect(l_screen, &src, SDL_MapRGBA( l_screen->format, 255,201, 0,255));
	/**<print candy bar*/
	src.x=dst.x = 575;
	energy=200*(((float)data->player.bp.currentVolume)/((float)data->player.bp.maxVolume));
	src.w = energy;
	SDL_FillRect(l_screen, &dst, SDL_MapRGBA( l_screen->format, 160, 32, 64,255));
	SDL_FillRect(l_screen, &src, SDL_MapRGBA( l_screen->format, 255, 128, 192,255));
	for(i=0; i<3; i+=2) {/**<Draw Text */
		char text[50];
		sprintf(text,"%d IN STASH",(data->player.candystash));
		SDL_Surface *message;
		TTF_Font *font = theFont(20);
		SDL_Color textColor = { 255*i, 255*i, 255*i,0};
		if (!(message = TTF_RenderText_Blended( font, text, textColor ))) {
			printf("%s\n",TTF_GetError());
			return 0;
		}
		TTF_CloseFont(font);
		SDL_Rect textRect = {275-i,22-i,0,0};
		if(0!=SDL_BlitSurface( message, NULL, l_screen, &textRect)) {
			printf("%s\n",SDL_GetError());
			return 0;
		}
		SDL_FreeSurface(message);
	}
	for(i=0; i<3; i+=2) {/**<Draw Text */
		char text[50];
		sprintf(text,"%d von %d",data->player.bp.currentVolume,data->player.bp.maxVolume);
		SDL_Surface *message;
		TTF_Font *font = theFont(10);
		SDL_Color textColor = { 255*i, 255*i, 255*i,0};
		if (!(message = TTF_RenderText_Blended( font, text, textColor ))) {
			printf("%s\n",TTF_GetError());
			return 0;
		}
		TTF_CloseFont(font);
		SDL_Rect textRect = {687-i,29-i,0,0};
		if(0!=SDL_BlitSurface( message, NULL, l_screen, &textRect)) {
			printf("%s\n",SDL_GetError());
			return 0;
		}
		SDL_FreeSurface(message);
	}
	SDL_FreeSurface(image_person);
	aStarPathPrint(data,l_screen);
	SDL_Flip(l_screen);
	return 1;
}
/**wandelt eine Position in Pixel auf eine Position auf dem Spielfeld um*/
position *pixelToGrid(position *l_pos)
{
	position *pos=calloc(1,sizeof( position));
	pos->x=(l_pos->x)/FIELDSIZE_FIELD;
	pos->y=(l_pos->y+10)/FIELDSIZE_FIELD;
	pos->next=NULL;
	return pos;
}
/**updatet die Scroll-Position des Spielfeldes*/
void verticalScrollPos( dataStore *data)
{
	int verticalScroll,verticalPos=data->player.p_pos.y,hScroll,hPos=data->player.p_pos.x;
	if(verticalPos<7)verticalScroll=0;
	else if (verticalPos>6 && verticalPos<FIELDSIZE_Y-5 )verticalScroll=verticalPos-6;
	else verticalScroll=FIELDSIZE_Y-12;
	data->verticalScroll=verticalScroll;
	if(hPos<9)hScroll=0;
	else if (hPos>8 && hPos<FIELDSIZE_X-7 )hScroll=hPos-8;
	else hScroll=FIELDSIZE_X-16;
	data->horizontalScroll=hScroll;
	if(DEBUG)printf("verticalScroll data/function: %d : %d\n",data->verticalScroll,verticalScroll);
}
/**updatet die Position der Spielfigur und führt die Interaktion mit dem Spielfeld aus
*zeigt außerdem die Animation des Schneidens an und wartet
*/
int headPositionUpdate(dataStore *data,position *newPos,SDL_Surface *l_screen)
{	

	
	position old=data->player.p_pos,n_pos=(*newPos);
	clock_t StartTime, StopTime,diffTime,innerStartTime;
	if(data->hedgewood[n_pos.y][n_pos.x].aStarValue<0)return 0;
	int x=0,y=0,vis=data->player.vision,i,j,animation=0,wait;
	SDL_Surface *image_animation=NULL;
	SDL_Rect src, dst;
	x=old.x-n_pos.x;
	y=old.y-n_pos.y;
	if(x<0)data->player.heading=1;
	if(x>0)data->player.heading=3;
	if(y<0)data->player.heading=2;
	if(y>0)data->player.heading=0;
	for(i=-vis; i<=vis; i++) {
		for(j=-vis; j<=vis; j++) {			
			if(n_pos.y+i>0&&n_pos.y+i<FIELDSIZE_Y &&n_pos.x+i>0&&n_pos.x+i<FIELDSIZE_X) {
				if(y>0 && i<0)data->hedgewood[n_pos.y+i][n_pos.x+j].visible=1;
				else if(x<0 && j>0)data->hedgewood[n_pos.y+i][n_pos.x+j].visible=1;
				else if(y<0 && i>0)data->hedgewood[n_pos.y+i][n_pos.x+j].visible=1;
				else if(x>0 && j<0)data->hedgewood[n_pos.y+i][n_pos.x+j].visible=1;
			}
		}
	}
	if(n_pos.y==2) {
		if(n_pos.x==7)data->player.currentEnergy=data->player.maxEnergy;
		else if(n_pos.x==13) {
			printf("CANDYSTASH: %d\n",data->player.candystash);
			data->player.candystash+=data->player.bp.currentVolume;
			data->player.bp.maxOverall+=data->player.bp.currentVolume;
			data->player.bp.currentVolume=0;
		} else if(n_pos.x==1) {
			storeStart(l_screen, data);
		}
	}
	GraphicUpdate(l_screen,data);
	

	wait=(data->hedgewood[n_pos.y][n_pos.x].aStarValue*60/data->player.cutSpeed)+100;
	if(data->hedgewood[n_pos.y][n_pos.x].type>8) {
		/**animation 20fps 10frames / durchgang*/
		animation=1;
		if ((image_animation =load_image(animation_pic))== NULL) {
			printf("Can't load image start: %s\n", SDL_GetError());
			exit(1);
		}
		src.w=dst.w =src.h=dst.h =40;
		StartTime = SDL_GetTicks();
		while(animation) {
			innerStartTime = SDL_GetTicks();
			
			/*Sound */
			if (!Mix_Playing(CHAINSAWCHANNEL2)&&data->soundEnabled) {
				Mix_PlayChannel(CHAINSAWCHANNEL2, data->chaingo, 0 );
			}
			
			src.x=src.y=(150-src.w)/2;
			dst.x=(n_pos.x-data->horizontalScroll)*FIELDSIZE_FIELD-50+src.x;
			dst.y=(n_pos.y-data->verticalScroll)*FIELDSIZE_FIELD-50+src.y;
			if(0!=SDL_BlitSurface(image_animation, &src, l_screen, &dst)) {
				printf("%s\n",SDL_GetError());
				return 1;
			}
			SDL_Flip(l_screen);
			if(dst.h<141)src.w=dst.w =src.h=dst.h +=11;
			else {
				GraphicUpdate(l_screen,data);
				src.w=dst.w =src.h=dst.h =40;
			}
			StopTime = SDL_GetTicks();
			diffTime = (StopTime-innerStartTime);
			if (50>diffTime)SDL_Delay(50-diffTime);
			if(StopTime-StartTime > wait)animation=0;
		}
		
		SDL_FreeSurface(image_animation);
	} else if(wait>0) {
		SDL_Delay(wait);
	}
	data->player.p_pos=n_pos;
	verticalScrollPos(data);
	return 1;
}
/**Zeichnet den Pfad des Players auf das Spielfeld*/
void aStarPathPrint(dataStore *data,SDL_Surface *l_screen)
{
	SDL_Surface *kreis=NULL;
	SDL_Rect  src,dst;
	if ((kreis =load_image(kreis_pic))== NULL) {
		printf("Can't load image start: %s\n", SDL_GetError());
		exit(1);
	}
	position *tmp=data->player.anfang;
	src.w=src.h=dst.w=dst.h=FIELDSIZE_FIELD;
	while(tmp!=NULL) {
		dst.x=(tmp->x-data->horizontalScroll)*FIELDSIZE_FIELD;
		dst.y=(tmp->y-data->verticalScroll)*FIELDSIZE_FIELD-10;
		if(tmp->next==NULL)src.x=50;
		else src.x=0;
		src.y=0;
		if(dst.y>=0)SDL_BlitSurface(kreis, &src, l_screen, &dst);
		tmp=tmp->next;
	}
	SDL_FreeSurface(kreis);
}
