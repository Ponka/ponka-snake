#ifndef __GAME_H__
#define __GAME_H__



#include"level.h"
#include"snake.h"
#include"screen.h"
#include"curses_ui.h"
#include"stuff.h"

/* zakonczenie tury gry czyli wartosc zwracana przez `game::next_step()'*/
#define GAME_OVER 	2	/* koniec gry */
#define CONTINUE	0	/* wszystko normalnie przebiega */
#define	AGAIN		1	/* waz ginie lub przechodzi poziom dalej */
#define EXIT		-1

#define YES	1	/* logiczne TAK */ /* troche to brzydki sposob 	*/
#define	NO	0	/* logiczne NIE */ /* tradycja rzekla, ze ladny */



/*
 * klasa `game'.
 */
class game
{
	public:
		game(ui *interface,Options *opt); /* TODO - config */
		~game();
		int game_loop(); 	/* wywolanie petli gry 		*/
		int return_score();	/* metoda zwracajaca wynik	*/
	private:
		int ssizex; /* te dwie zmienne mozna wyciagnac metoda z 
			       klasy SCREEN lub z XXX config`u */
		int ssizey; 
		/* chyba jasne? ;) */
		int score;
		int level_nr;	
		int lives ;
		int nfo_ssizey ; 
		Options *opt ; 
		/* wskazniki na klasy inicjowane w konstruktorze */
		level *lev; 
		snake *sn;
		screen *scr;
		ui *in;
		/* prywatne metody tej klasy */
		void game_loop_idle();		/* pauza petli gry 	*/
		int key_watch();		/* sprawdzenie klawiszy */
		void start_at_level(int l);	/* nowa plansza:level(l)*/
		void give_food();		/* nakarmienie weza 	*/
		int fail();			/* nie udalo sie	*/
		int success();			/* udalo sie		*/
		int quit();			/* wychodzimy z gry */ 
};




#endif	/* __GAME_H__	*/
