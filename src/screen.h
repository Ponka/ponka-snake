#ifndef __SCREEN_H__
#define __SCREEN_H__

#include"config.h"
#include"curses_ui.h"
#define STATUS_SIZE_Y 2 
/*
 *   struktura typu  - Point - .
 */   
struct point {
		int x;
		int y;
		char type;// rodzaj danego punktu.	
};
typedef struct point Point; /* Typ struktury point */

/*
 *  KLASA - screen. 
 */ 
class screen //  TODO - zmieniana wielkosc ekranu .
{
	public :
		/* konstruktor i destruktor klasy */	
		screen(Options *o , ui *in);
		~screen();
		/* metody obslugi poszczegolnych punktow macierzy ekranu */	
		char chk_point(Point p);
		void set_point(Point p) ;
/* ustawienie paska stanu gry */ // XXX -- gry a nie ekranu - wiec WON !
		void set_status_bar(int score, int level, int lives);
		/* pobieranie wielkosci planszy */	
		int get_sizex();
		int get_sizey();
		/* wyswietlanie ekranow informacyjnych */	
		void show_nfo_scr(char *buf);
		void set_info_bar(char *buf);/* XXX NOWE - uzyj XXX */
	
		void display(); /* wyswietla */
		void clear();/* czyszczenie weza */
	private:
		/* +>Metody prywatne<+ klasy */
		void make_txt_screen(); /* zamazanie ekranu */
		void set_info_bar(); /* ustawienie paska `info' */
		void set_point_in_status(Point p);
		void set_info_point(Point p);
		/* +>Dane prywatne<+ klasy */
		Point **scr;
		char **status ;/* TODO */	
		char **info; /* TODO */
		ui *i; /* interfejs wyswietlania */
		Options *opt ; /* struktura przechowujaca opcje gry */
		int sizex;
		int sizey;
		int ssizey;
		int isizey;
};



#endif /* ___SCREEN_H__ */
