
#include<stdlib.h>		/* malloc();		*/
#include<string.h>		/* strlen();		*/
#include<stdio.h>		/* sprintf();		*/

/* uzywane jedynie w metodzie `screen::display()', za to nie raz.. */
/* zmiana interfejsu uzytkownika bedzie wymagala jej ruszenia */
#include<ncurses.h>

#include"screen.h"


/* definicje etykiet na potrzeby wewnetrzne */

/* klasa - > screen < - */
#define STATUSBAR_Y 	3
#define INFOBAR_Y	1

char *status_txt[] = { /* TODO - text w pasku informacyjnym wydelegowac OUT*/
	 "sc0re : ", 
	 "level : ", 
	 "lives : "
};

/*
 *  	KLASA :
 * ----------->  screen  <------------  
 *			macierz wirtualnego ekranu i jego obsluga.
 * XXX XXX
 */

 /* 
  *  >> konstruktor << -
  */
screen::screen(Options *o, ui *in)
{
	int x,y;	
	opt = o ;	
	sizex = opt->sizex;
	sizey = opt->sizey;
	i = in ; 
	/*	zmienne, poki co sa stale :> .. zasieg lokalny */	
	ssizey = STATUSBAR_Y;
	isizey = INFOBAR_Y;
	scr = (Point**)malloc ((size_t)opt->sizex * sizeof(Point*));	
	status=(char**)malloc ((size_t)opt->sizex * sizeof(char*));	
	info=(char**) malloc ((size_t)opt->sizex * sizeof(char*));	

	for(x = 0 ; x < opt->sizex ; x++ )
	{
		scr[x]=(Point*) calloc((size_t)sizey,sizeof(Point)) ; 
		status[x] = (char*)calloc((size_t)ssizey, sizeof(char)) ; 
		info[x]= (char*) calloc( (size_t)isizey , sizeof(char)) ; 
	}
	set_info_bar();		

	for ( x = 0 ; x < opt->sizex ; x++)
	{
		for ( y = 0 ; y < opt->sizey ; y++)
		{	
			scr[x][y].type = opt->background ; 
			scr[x][y].x = x ;
			scr[x][y].y = y ; 
/*			if ( y < ssizey )
				status[x][y] = opt->statusbackground;*/
		}
	}	
}
/*  >> destruktor << -  */
screen::~screen( )
{
	free(scr);
	free(info);
	free(status);
}

char screen::chk_point(Point p)
{
	return scr[p.x][p.y].type;	
}

void screen::set_point(Point p)
{
	scr[p.x][p.y].type = p.type ; 
}



void screen::set_status_bar(int score, int level, int lives)
{
	
	int i ;
	int val[STATUS_SIZE_Y]; 
	val[0] = score ; 
	val[1] = level ;
	val[2] = lives ;
	//fprintf(stderr,"SET_STATUS_BAR : lives : %d\n",lives );
	sprintf(status[0],"%s%d",status_txt[0],score);
	sprintf(status[1],"%s%d",status_txt[1],level);
	sprintf(status[2],"%s%d",status_txt[1],lives);


}
void screen::set_info_bar()
{
	set_info_bar(INFO_TXT);
}

void screen::set_info_bar(char *buf)
{
	size_t len; 
	len = strlen(buf);
	if((int)len <= opt->sizex )
		strcpy(info[0],buf) ;
	else 
		strncpy(info[0],buf,opt->sizex);
	
}
int screen::get_sizex()
{
	return opt->sizex;
}

int screen::get_sizey()
{
	return opt->sizey;
}

		
void screen::show_nfo_scr(char *ch)
{
	int i, start ; 
	int len ;

	make_txt_screen();
	len = strlen(ch) ;
	start = (opt->sizex / 2 ) - (len / 2) ;  
	attrset(COLOR_PAIR(2));
	for ( i = 0 ; i < len ; i++ )
		scr[start + i ][opt->sizey / 2].type = ch[i] ; 
	display();
}

void screen::make_txt_screen()
{
	int i,j ;

	for(i = 0 ; i < opt->sizex ; i++ ) 
		for( j = 0; j < opt->sizey ; j++ ) 
			scr[i][j].type = opt->txtbackground ; 
}


/*
 *                                     DISPLAY 
 */
void screen::display()
{   
	int x , y;
	erase(); // -- XXX -- do ui !
	
	for(  y = 0 ; y < opt->sizey ; y ++ )
		for (  x = 0 ; x < opt->sizex ; x++) 
			i->display_point(y, x , scr[x][y].type);

	for(; y < opt->sizey + ssizey ; y ++ )
		i->display_string(y,1, status[y-opt->sizey]);//XXX colors
	
	for(  y = opt->sizey+ssizey ; y < opt->sizey + ssizey + isizey ; y ++ )
		i->display_string(y,1,info[y-opt->sizey-ssizey]);//color XXX.
	refresh(); // -- XXX -- do ui ! 
}
void screen::clear()
{
	int x,y;
	for(x = 0 ; x < opt->sizex ; x++)
		for(y=0; y < opt->sizey ; y++)
			if((scr[x][y].type!=TRAP)&&(scr[x][y].type!=opt->food))
				scr[x][y].type = opt->background ;
}



