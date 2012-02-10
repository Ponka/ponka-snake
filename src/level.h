#ifndef __LEVEL_H__
#define __LEVEL_H__



#include"screen.h"
#include"config.h"
#include"stuff.h"

/*
 * klasa `level'.
 */


class level 
{
	public:	
		level(int i,Options *cfg);
		~level();
		void set_traps(screen * s);/* rysuje plansze poziomu */
		int chk_if_end(int snake_size);/*czy konczyc poziom?*/
		int chk_speed();
	private:
		Options *opt ; 
		int nr_of_traps; /* liczba plapek aktualnego poziomu */
		int end_size; 	/* wielkosc weza konczaca poziom XXX usun*/
		int speed ;   	/* --=<<+>--+-=|[5p33]]|=-+--<+>>=--	*/
};




#endif	/* __LEVEL_H__	*/
