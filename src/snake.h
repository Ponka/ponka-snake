#ifndef __SNAKE_H__
#define __SNAKE_H__


#include"stuff.h"
#include"screen.h" /* typ Point; screen::set_point(Point); */ 
//#include"game.h"


/* definicje makr dla weza */
#define MAX_SNAKE_SIZE ((SCREEN_SIZE_X - 2)*(SCREEN_SIZE_X-2))//duzy nadmiar  
/* XXX - gdy bedzie konfig stanie sie zbedne XXX to wyzej tez */
#define DEFAULT_START_SNAKE_X (SCREEN_SIZE_X / 2)/* domyslnie rzucamy weza */
#define DEFAULT_START_SNAKE_Y (SCREEN_SIZE_Y / 2)/* na srodeczek */

/* _____| . |__\__________ /__________________/.    .   .    .     .      .
 * _____KLASA___>\......./<_________________/.    .    .     .      .       .
 * _____| . |___>>>snake<<<_______________/.     .    .      .       .        .
 * _____| . |___>/^^^^^^^\<_____________/.     .     .       .        .        
 * _____| . |__/  _/^^^\_  \__________/.     .      .        .         .     
 */ 
class snake 
{
	public:	
		snake( Options *o );//TODO 	/* konstruktor	TODO startxy */
		~snake();			/* destruktor 	    */
		Point move(int direction); 	/* ruch (zwraca pozycje glowy)*/
		int resize(int vector);		/* zwiekszanie weza  */

		/* pseudofunkcja get_snake_size() */
#define 	get_snake_size() 	resize(0)	
		
		void print(screen *s); 			/* rysuje weza   */
		int get_mov_direction();		/* kierunek ruchu*/
	private: 
		Options *opt;
		Point *snk_bod;			/* punkty weza 	  */
		int snk_l; 				/* rozmiar	  */
		int mov_direction;			/* kierunek ruchu */	
		int resize_f;				/* czy wydluzyc   */
};



#endif /* __SNAKE_H__ */
