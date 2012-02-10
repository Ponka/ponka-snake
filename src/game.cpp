
#include<stdlib.h>
#include<unistd.h>
#include"game.h"



/*
 *   KLASA - > game < -------------------------------- XXX GAME XXX ----<+>--
 *   	       ^^^^
 */
game::game(ui *interface, Options *op)
{
	opt = op ; 		
	score = 0 ;
	level_nr = 1 ;
	lives = opt->lives;
	
	in = interface;	

	nfo_ssizey = STATUS_SIZE_Y;/* XXX???XXX???XXX */	
	
	scr = new screen (opt,in);	
	
	lev = new level (1,opt) ;
	
	int snake_size ; 
	snake_size = (int)opt->startsize ; 
	sn = new snake(opt);
	lev->set_traps(scr);
	give_food();
}
game::~game()
{
	delete lev ;
	delete sn ;
	free(opt);
	free(scr);
}	

/*
 * GAME - game_loop ();
 * wartosci zwracane : 	GAME_OVER
 *			CONTINUE
 */
int game::game_loop()
{
	int in ;
	char ch ;
	ch = opt->background;
	scr->clear();/* czyscimy plansze */
	sn->print(scr);/* rysujemy nowe polozenie weza */
	//fprintf(stderr,"GAME_LOOP lives : %d \n",lives);
	scr->set_status_bar(score,level_nr,lives);/* ustawiamy pasek wyniku*/  
	scr->display();/* wyswietlamy */

	game_loop_idle();
	in = key_watch();
 	/* obsluga wejscia uzytkownika */	
	if ( in == QUIT ) 
		quit();
	/* ruszamy weza i dostajemy typ pola na ktory sie rusza */
	if (( in != NON) && ( in != NEXT )&&(in != QUIT) ) /* jezeli (nie NON) i (nie NEXT) */
		ch = scr->chk_point(  sn->move(in) );
	/* ruszamy sami wezem gdy uzytkownik tego nie zrobil sam */
	if (( in == NON ) && ( sn->get_mov_direction() != 0))
			ch = scr->chk_point(sn->move(sn->get_mov_direction()) );
	if( in == QUIT ) 
		return EXIT ; 
//	/* sprawdzamy na co wdepnelismy ;) */
	if ( ch == opt->food ) /* XXX jezeli to jedzonko */
	{
		score ++;/* punkt */
		sn->resize(1);/* powiekszamy weza */
		give_food();/* wrzucamy rzarcie */	
	}
	if( (ch == TRAP)||(ch == opt->snakebody ))/*XXX */
		return fail();
	
	/* sprawdzamy czy konczymy poziom */
	if(lev->chk_if_end(sn->get_snake_size() ) == YES )
		return success();
	
	
	return 0 ;
}
int game::key_watch()
{
	int i= in->keypress();
	usleep(1) ;
	return i; //ui_keypress();
}
int game::quit()
{
	/* XXX TODO -  >> USER INTERFACE <<  - TODO XXX */
	return EXIT ; 	
}
int game::fail()
{
	lives -- ;
	if ( lives == -1 )
	{
		scr->show_nfo_scr(" GAME OVER "); // TODO -  uogolniona show_nso_scr
		return GAME_OVER ;
	}
	scr->show_nfo_scr(" UPS ! ");//TODO - uogolniona show_nso_scr		
	start_at_level(level_nr);
	return 0 ;
	
}
int game::success()
{
	
	score = score + (level_nr * 10);
	if ((level_nr % opt->levelbonus) == 0 ) 
		lives ++ ;
	level_nr ++ ;	
	scr->show_nfo_scr(" NEXT LEVEL ! ");//TODO - teraz uogolniona show_nso_scr			

	start_at_level(level_nr);	
	return 1; 
}	


void game::start_at_level(int l)
{
	delete lev;
	delete sn;
	lev = new level(l,opt); 	
	sn = new snake( opt  );
	
	/* czekaj na klawisz XXX - nie zadziala w non blocking mode */
	while( key_watch() != NEXT );//XXX
	delete scr ;
	/* TODO TODO -- teraz tylko przyjmuje 2 argumenty - TODO TODO */
	scr = new screen ( opt, in);
	lev->set_traps(scr);
	give_food();
}
void game::give_food()
{
	Point tmp;
	tmp.type = opt->food ; 
	tmp.x = get_random(scr->get_sizex() - 1) ;
	tmp.y = get_random(scr->get_sizey() - 1) ;
	if ( scr->chk_point(tmp) == opt->background ) /* XXX TODO CONFIG */
		scr->set_point(tmp);
	else
		give_food();
}
void game::game_loop_idle()
{
	/* XXX XXX XXX   CONFIG   XXX XXX XXX */
	usleep((ulong)opt->speedstart-(lev->chk_speed()*opt->speedupfreq));
}

int game::return_score()
{
	return score ;
}

