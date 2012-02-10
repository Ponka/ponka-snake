#include"curses_ui.h"
#include"game.h"
#include"config.h"
#include"hiscore.h"
#include<stdlib.h>

/* naglowek interfejsu TODO - oddzielic od kodu interfejs uzytkownika */
char *menu_names[] = {
			" Start game. ",
			"Sea hiscores.",
			"  Options.   ",	
			"    Exit.    ",
};

int playGame(ui *in , config *cfg) ;	
void show_hiscore(ui *in);
void game_is_over(ui *in ,int score);


int main (void)
{
	int ret;
	config *cfg ;
	ui *in ;
	ui_menu *start_menu ; 
//	hiscore score ; 
	cfg = new config  ;
	in = new ui (cfg->get_opt()) ; 
	start_menu = new ui_menu (4,menu_names);
//	in->get_nick();
	in->keypress(K_BLOCK);
	while(1)
	{
		ret = start_menu->InOutKeys(in->keypress()); 
		switch(ret )
		{
			case 1  :
				in->keypress(K_NOBLOCK) ;
				ret = playGame(in,cfg);
				delete start_menu ;
				start_menu = new ui_menu(4,menu_names);
				in->keypress(K_BLOCK) ;
				break ; 	
			case 2 : 
				 show_hiscore(in);
				 delete start_menu ;
				 start_menu = new ui_menu(4,menu_names) ; 
				 break ;/*TODO - options - config */
			case 3 : 
				 break ; /* TODO - hiscores */
	 		case 4 : 
				ret = EXIT ; 
				 break ;
		}
		
		if(ret == EXIT)/* TODO - czy napewno wyjsc? */
			break ; 
	}
	/* TODO - exit screen */
	delete start_menu ;
	delete in ; 
	return 0 ;
}


int playGame(ui *in,config *cfg)
{
	game *mygame ;
	int ret = CONTINUE ;
	mygame  = new game (in,cfg->get_opt()); // zaczynamy gre. 
	while( ret  != GAME_OVER && ret != EXIT)  
	{
		ret = mygame->game_loop() ;
		
	}
	if ( ret == EXIT )
		return EXIT ;
	/* TODO - hiscore */
	if ( ret == GAME_OVER )
		game_is_over(in ,mygame->return_score());	 
		
	delete mygame ;
	return 0;
}
void show_hiscore(ui *in)
{
	hiscore *hi ;
	
	hi = new hiscore ;
	in->display_hiscore(hi->get_list());	
	delete hi ; 
}
void game_is_over(ui *in ,int score)
{
	hiscore *hi ; 
	char *nick ; 
	hi = new hiscore ;
	if (hi->chk_if_good(score)== 1)
	{
		nick = in->get_nick(); 
		in->display_hiscore(hi->get_list(nick));
	}
	else 
		in->display_hiscore(hi->get_list());
	delete hi ;
//	free(nick); // TODO TODO
}	
	
