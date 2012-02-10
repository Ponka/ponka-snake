#ifndef __CONFIG_H__
#define __CONFIG_H__




/* definicje makr dla ekranu */
#define SCREEN_SIZE_X 30	 
#define SCREEN_SIZE_Y 20
/* definicje makr dla znakow wyswietlania */
#define SNAKE_HEAD 		'@'
#define SNAKE_BODY		'o'
#define BACKGROUND		'.'
#define TRAP			'*'
#define FOOD			'$'
#define TXT_BACKGROUND		'#'
#define STATUS_BACKGROUND 	' '
#define INFO_BACKGROUND		' '
#define INFO_TXT "(q)uit;(p)ause;"
/* ustawienia gry - GAME SETING */
#define START_LIVES			3/* poczatkowe zycia weza */
#define POINTS_PER_FOOD			1/* punkty za zjedzone jedzonko */
#define LEVEL_BONUS			5/* co ile poziomow dodatkowe zycie? */
#define SPEEDUP				4/* co ile poziomow przyspieszamy ? */
#define TRAPS_BY_LEVEL			3/* ile plapek na poziom? */
#define START_SNAKE_SIZE 		6/* poczatkowa dlugosc weza */ 
#define FINISH_SNAKE_SIZE_BY_LEVEL (START_SNAKE_SIZE + 1)/*jaki waz ma byc?*/
/* definicja jednostki czasu w nanosekundach */
#define START_IDLE 		100000
#define	IDLE_LESS_PER_LEVEL 	20000	


typedef unsigned long ulong ;
struct gameopt_s  
{
	int sizex ;		//+++++++++++++++++++++++
	int sizey ;		// rozmiar planszy +++++
	int startsize ;		// wielkosc poczatkowa <<<
	int lives ;		// ilosc zyc =============================
	int ptsperfood ;	// punkty za zjedzenie ==============
	int trapsperlevel;	// plapki na poziom ===============
	int endsizeperlevel;	// wymagana wielkosc na level ===
	int levelbonus ;	// co ile leveli extra live =======
	ulong speedstart;	// poczadkowa predkosc -----------
	ulong speedupfreq;	// co ile leveli przyspieszac ----- speed
	ulong speedupval;	// o ile przyspieszac -------------
	char snakehead;		// 
	char snakebody ;	// 
	char background;	//
	char trap;		// 
	char food;		//
	char txtbackground;	//
	char statusbackground;	//
	char infobackground; 	//       
};
typedef struct gameopt_s Options ;

class config
{
	public:
		config();
		~config();
		Options *get_opt();
		void set_opt(Options *opt);
	private:
		Options *op;
};

#endif /* __CONFIG_H__ */
