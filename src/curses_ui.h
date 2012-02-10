#ifndef __CURSES_UI_H__
#define __CURSES_UI_H__

#include <form.h>
#include<menu.h>
#include"stuff.h"
#include"config.h"
#include"hiscore.h"

#define SCR_FAIL	1
#define	SCR_SUCCESS	2
#define	SCR_GAMEOVER	3

/* opcje do metody ui::keypress(int); */
#define K_NOBLOCK	0	/* tryb nieblokujacy */
#define K_BLOCK		1	/* tryb blokujacy */
#define K_CHK		2	/* sprawdz tryb */

class ui
{
		public:
			ui(Options *op);
			~ui();

			int keypress();/* czytajaca klawisze */
			int keypress(int mode);/* czytajaca klawisze */
			/* obsluga listy rekordow i pobierania nicka */
			/* obsluga ekranu gry */
			void display_point(int y , int x,char ch);
			void display_string(int y,int color,char *buf);
			int nfo_scr_drv(int kind );
			void display_hiscore(Score *list) ;
			char *get_nick(void) ; /* TODO */
		private:
			void print_in_middle(WINDOW *win,int starty,int startx,int width,char *string, chtype color);
			int nick_key_filter(int ch); 
			
			Options *opt ;
};
class menu 
{
	public:
		menu(int choices,char **names,char **descr);
		menu(int choices,char **names);
		~menu();
		void Refresh();
		int InOutKeys(int key);
	private: 
		WINDOW *menuwin;
		ITEM **m_items ;
		MENU *m_menu;
		ITEM *c_item;
		int nr_items;		
		int current ;
};

typedef class menu ui_menu ; 

#endif /* __CURSES_UI_H__ */		

