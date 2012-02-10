
#include<stdlib.h>	/* random(); 	*/

#include"level.h"




/*
 *   KLASA - > level < -
 *   	       ^^^^^
 */
level::level(int i , Options *cfg) 
{
	opt = cfg ; 
	speed = (i * opt->speedupfreq) / opt->speedupfreq ;  
	nr_of_traps = i * opt->trapsperlevel ;
	end_size = opt->endsizeperlevel * i ;
}


level::~level()
{
}

void level::set_traps(screen * s)// --- TODO
{
	Point tmp; 	
	int i,x,y;	

	x = s->get_sizex();
	y = s->get_sizey();
	tmp.type = opt->trap ;
	for (  i = 0 ; i < nr_of_traps; i++) 		
	{
		tmp.x = get_random(x - 1) ;
		tmp.y = get_random(y - 1) ;
		s->set_point(tmp);
	}	
	for ( i = 0 ; i < x ; i++)
	{
		tmp.x = i ;
		tmp.y = 0 ;
		s->set_point(tmp);
		tmp.y = y - 1 ;
		s->set_point(tmp);
	}
	for (i = 0 ; i < y ; i ++ ) 
	{
		tmp.y = i ;
		tmp.x = 0 ;
		s->set_point(tmp);
		tmp.x = x - 1 ;
		s->set_point(tmp);
	}

}
int level::chk_if_end(int snake_size )
{
	if  (snake_size >= end_size) 
		return 1;
	return 0;
}
int level::chk_speed()
{
	return speed ;
}

