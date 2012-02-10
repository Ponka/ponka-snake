#include<stdlib.h>
#include "config.h"
config::config()  	
{
	
	op = (Options*) malloc(sizeof(Options));
	op->sizex 		= 	SCREEN_SIZE_X;	
	op->sizey 		= 	SCREEN_SIZE_Y;
	op->startsize 		= 	START_SNAKE_SIZE;
	op->lives 		=	START_LIVES ;
	op->ptsperfood 		= 	POINTS_PER_FOOD;
	op->trapsperlevel 	=  	TRAPS_BY_LEVEL;
	op->endsizeperlevel 	= 	FINISH_SNAKE_SIZE_BY_LEVEL;
	op->levelbonus 		= 	LEVEL_BONUS;	
	op->speedstart 		= 	START_IDLE ;	
	op->speedupfreq 	= 	SPEEDUP;
	op->speedupval 		= 	IDLE_LESS_PER_LEVEL;
	op->snakehead 		= 	SNAKE_HEAD; 
	op->snakebody 		= 	SNAKE_BODY ; 
	op->background 		= 	BACKGROUND;	
	op->trap 		= 	TRAP;	 
	op->food 		= 	FOOD;		
	op->txtbackground 	= 	TXT_BACKGROUND;
	op->statusbackground 	= 	STATUS_BACKGROUND;
	op->infobackground 	= 	INFO_BACKGROUND; 

}

config::~config()
{
	free(op);
}
Options *config::get_opt()
{
	Options *tmp ; 
	tmp = (Options*)malloc(sizeof(Options));
	*tmp = *op ; 
	return tmp ;
	
}
void config::set_opt(Options *opt)
{
	
	op->sizex 		=opt->sizex ;		
	op->sizey 		=opt->sizey ;		
	op->startsize 		=opt->startsize ;		
	op->lives 		=opt->lives ;		
	op->ptsperfood 		=opt->ptsperfood ;		
	op->trapsperlevel 	=opt->trapsperlevel ;	
	op->endsizeperlevel 	=opt->endsizeperlevel ;	
	op->levelbonus 		=opt->levelbonus ;		
	op->speedstart 		=opt->speedstart ;		
	op->speedupfreq 	=opt->speedupfreq ;	
	op->speedupval 		=opt->speedupval ;		
	op->snakehead 		=opt->snakehead; 		
	op->snakebody 		=opt->snakebody ;		
	op->background 		=opt->background ;		
	op->trap 		=opt->trap 	;	
	op->food 		=opt->food 	;	
	op->txtbackground 	=opt->txtbackground; 	
	op->statusbackground 	=opt->statusbackground; 	
	op->infobackground 	=opt->infobackground ;	
}

	
