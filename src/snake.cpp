#include<stdlib.h>


#include"snake.h"



/* _____|____\\+-/\+/X\+/\-+//| . |___________/.   .  .  ..  .  .. .    .. . 
 * _____KLASA+>>-\/_\_/_\/-<<+| .||_________/.    ...    ..    ...  .  .. .  
 <+>>-<|||=-=>>=>>>SNAKE<<<=<<=-=|||>-<<+>/..... .. .. ....................... 
 * _____||. |+>\-/=-=#=-=\-/<+| .||_____/.   .  .. . ..  ..  ... ..  .. .....  
 * _____| . |/_/^\_-+|+-_/^\_\| . |___/.  .  . .. . . .. .. ............      
 */  	 

/*  konstruktor weza */
snake::snake(Options *o)
{
	Point start ;
	opt = o ; 
	snk_l = opt->startsize ; 	
	start.x = opt->sizex / 2 ;
	start.y = opt->sizey / 2 ;
	int i ;
	resize_f = 0 ;
	mov_direction = 0 ;
	snk_bod = (Point*) calloc((size_t)snk_l ,  sizeof(Point) ) ;
	
	for( i = 0 ; i < snk_l ; i++ )
	{
		snk_bod[i].x = start.x + i ;
		snk_bod[i].y = start.y ;
		if(i == 0 ) 
			snk_bod[i].type = opt->snakehead ;
		else
			snk_bod[i].type = opt->snakebody ;
	}
}

snake::~snake()
{
	free(snk_bod);
}
Point snake::move(int direction)
{
	Point head;
	Point *snake_new;

	head.type = opt->snakehead ;
	mov_direction = direction ; /* zapamietanie kierunku ruchu weza */
	switch (direction)
	{
		case UP :  head.x = snk_bod[0].x ;
			   head.y = snk_bod[0].y - 1;
			   break;
		case DOWN : head.x = snk_bod[0].x ;      
                            head.y = snk_bod[0].y + 1;
                            break;
		case LEFT : head.x = snk_bod[0].x - 1;      
                            head.y = snk_bod[0].y ;
                            break;
		case RIGHT : head.x = snk_bod[0].x + 1;      
                            head.y = snk_bod[0].y ;
                            break;
	}
	int i ;	
	
	snake_new = new Point[snk_l + resize_f] ;
	
	for ( i = 0 ; i < snk_l + resize_f ; i++ )
	{ 
			if( i == 0 )
			{
				snake_new[i].type=head.type ;
				snake_new[i].x = head.x ; 
				snake_new[i].y = head.y ;
			}
			else if( i < snk_l  )
			{	
				snake_new[i].x = snk_bod[i-1].x ;
				snake_new[i].y = snk_bod[i-1].y ;
				snake_new[i].type = opt->snakebody ;
			
			}
			else if ( i >= snk_l )
			{
				if(resize_f != 0) 
				{
					snake_new[i].x = snk_bod[i-1].x;
					snake_new[i].y = snk_bod[i-1].y;
					snake_new[i].type = opt->snakebody;
					//fprintf(stderr, "resizezero");
			
				}
				else 
					snake_new[i].type=opt->background;
				
			}

	}
	if(resize_f != 0 ) 
		snk_bod=(Point*)realloc(snk_bod,(size_t)(snk_l+resize_f)* sizeof(Point) ) ;

	for (i = 0 ; i < snk_l+resize_f ; i++ ) 
	{
		snk_bod[i].x = snake_new[i].x ;		
		snk_bod[i].y = snake_new[i].y ;		
		snk_bod[i].type = snake_new[i].type ;		
	
	
	}
		
	
	snk_l = snk_l + resize_f ;
	resize_f = 0 ; 
	delete snake_new ; 
	return head ; 
}
int snake::resize(int vector)
{
	resize_f = resize_f + vector;/*zaznaczenie flagi zmiany wielkosci weza*/
	return snk_l ;
}
int snake::get_mov_direction()
{
	return mov_direction ; 
}
void snake::print(screen *s)/* screen.h - XXX - moze inaczej ? */
{
	int i ;
	for ( i = 0 ; i < snk_l  ; i++ )
		s->set_point(snk_bod[i]);/* screen.h- XXX -moze inaczej ? */
}
	
