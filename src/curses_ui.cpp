#include"curses_ui.h"
#include<stdlib.h>  /* menu	*/ 
#include<string.h>



ui::ui(Options *op)
{
	opt = op ; 
	initscr();
	keypad(stdscr,TRUE);
	noecho();	
	nodelay(stdscr,TRUE);
	start_color();				// 0 tez ;> 
	init_pair(1,  COLOR_WHITE	,COLOR_BLACK); // 
	init_pair(2,  COLOR_CYAN	,COLOR_BLACK);
	init_pair(3,  COLOR_MAGENTA	,COLOR_BLACK);
	init_pair(4,  COLOR_BLUE	,COLOR_BLACK);
	init_pair(5,  COLOR_YELLOW	,COLOR_BLACK);// * 
	init_pair(6,  COLOR_GREEN 	,COLOR_BLACK);// * 
	init_pair(7,  COLOR_RED   	,COLOR_BLACK);

}


ui::~ui()
{
	int i ; 
	for(i=0 ; i <20 ; i++)
		flash();
	endwin();
}



int ui::keypress()
{
	int ch ;
	ch = getch();
	switch(ch)	
	{
		case 259 : return UP ;
		case 258 : return DOWN;
		case 260 : return LEFT;
		case 261 : return RIGHT;
		case 113 : return QUIT ;
		case 32 : return NEXT;
		case 10 : return NEXT;
	}
	return 0 ;
}
int ui::keypress(int mode)
{
	switch(mode)
	{
		case 0 :nodelay(stdscr,TRUE);
			return 0;
			break;
		case 1 :nodelay(stdscr,FALSE);
			return 0;
			break;
		default: return -1;
	}
	return -2;
}



void ui::display_point(int y, int x, char ch)
{

	int maxx,maxy,startx ; 
	getmaxyx(stdscr,maxy,maxx) ; 
	startx  = (maxx/2) - (opt->sizex/2)    ; 
	if (ch == opt->food )
		attrset(COLOR_PAIR(5));
	if (ch == opt->background ) 
		attrset(COLOR_PAIR(0));
	if (ch == opt->snakebody )
		attrset(COLOR_PAIR(6));
	if (ch == opt->trap )
		attrset(COLOR_PAIR(7));
	if (ch == opt->snakehead )
		attrset(COLOR_PAIR(2)) ; 
	mvaddch(y , x + startx , ch ) ; 
}	
int ui::nfo_scr_drv(int kind)
{
	return 0 ; //TODO
}
void ui::display_string(int y,int color,char *buf)
{
	int x ;
	getmaxyx(stdscr,x,x);
	x = x/2 - opt->sizex / 2 ; 
		
	attrset(COLOR_PAIR(color));
	mvprintw(y,x,"%s",buf);
}



/*
 *  class 	XXX 	MENU	XXX 
 */
menu::menu(int choices,char **names, char **descr)
{
	int i,y,x ;
	nr_items = choices;
	getmaxyx(stdscr,y,x);

	m_items = (ITEM**) calloc(choices + 1 , sizeof(ITEM*));
	for(i = 0 ; i < choices ; i++)
		m_items[i] = new_item(names[i] , descr[i] ) ;
	m_items[choices] = (ITEM*) NULL ;
	
	m_menu = new_menu((ITEM**)m_items);
	
	post_menu(m_menu);
	refresh();
}	
menu::menu(int choices,char **names)
{
	int i,maxy,maxx,y,x ;
	/* pierwsza pozycja w menu zawsze na poczadku podswietlona */
	current = 1 ;
	nr_items = choices ; 
	getmaxyx(stdscr,maxy,maxx);
	m_items = (ITEM**) calloc(choices + 1 , sizeof(ITEM*));
	for(i = 0 ; i < choices ; i++)
		m_items[i] = new_item(names[i] , NULL ) ;
	m_items[choices] = (ITEM*) NULL ;
	clear();
	m_menu = new_menu((ITEM**)m_items);
	set_menu_fore(m_menu,COLOR_PAIR(4)|A_UNDERLINE);
	set_menu_back(m_menu,COLOR_PAIR(5));
	set_menu_grey(m_menu,COLOR_PAIR(6));
	scale_menu(m_menu , &y , &x ) ; 
	menuwin = newwin(3*y,x+x,maxy/4 - y/2,maxx/2 - x);
	keypad(menuwin,TRUE);	
	set_menu_win(m_menu,menuwin);
	set_menu_sub(m_menu,derwin(menuwin,y,x,y,x/2));	
	box(menuwin,0,0);
	refresh();
	post_menu(m_menu);
	wrefresh(menuwin);
}	



menu::~menu()
{
	int i;
	for(i = 0 ; i < nr_items ; i++)
		free_item(m_items[i]) ;
	free_menu(m_menu);
}
void menu::Refresh()
{
	clear();
	current=1; 
	menu_driver(m_menu,REQ_FIRST_ITEM);
	wrefresh(menuwin);
	
}
int menu::InOutKeys(int key)
{

  //fprintf(stderr,"key:%d , current %d , nr_items %d \n",key,current,nr_items);
	switch(key)
	{
		case UP : 	
			
			if(current <= 1 )
			{
				menu_driver(m_menu,REQ_LAST_ITEM);
				current = nr_items ;
			}
			else
			{
				menu_driver(m_menu,REQ_UP_ITEM);
				current -- ;
			}
			break;
		case DOWN:
			if(current >= nr_items ) 
			{
				menu_driver(m_menu,REQ_FIRST_ITEM);
				current = 1 ;
			}
			else 
			{
				menu_driver(m_menu,REQ_DOWN_ITEM);
				current ++ ; 
			}
			break;
		case QUIT:
			return QUIT; // - TODO - makro 
		case NEXT :
		  //fprintf(stderr,"menu choice : %d\n",current);
			return current;
		
		default:
			break;
	}	
	
	wrefresh(menuwin);
	return 0 ;		
}
void ui::display_hiscore(Score *list) 
{
	int i,col ;
	erase();	
	for ( i = 0 ; i < MAX_HISCORE ; i++ ) 
	{
		col = (i % 6) +1; 
		attrset(COLOR_PAIR(col));

		mvwprintw(stdscr ,i,1,"DISPLAY:%d:%d:%s: \n",i,list[i].score , list[i].nick) ;
	}
	refresh();
	getch();
}
char *ui::get_nick(void)
{
	char *nick;
	FIELD *field[2];
	FORM  *my_form;
	WINDOW *my_form_win;
	int ch=0, rows, cols,pos=0,maxx,maxy;
	getmaxyx(stdscr,maxy,maxx);
	nick = new char [MAX_NICK+1] ; 
	bzero((void*)nick,(size_t)(MAX_NICK+1)*(sizeof(char)));
	//fprintf(stderr,"GET_NICK:maxx:%d:maxy:%d:\n",maxx,maxy);
	keypress(K_BLOCK);
	erase();	
	field[0] = new_field(1, MAX_NICK, 0, 3, 0, 0);
	field[1] = NULL;

	set_field_back(field[0], A_UNDERLINE);
	field_opts_off(field[0], O_AUTOSKIP); /* Don't go to next field when this */
	my_form = new_form(field);
	scale_form(my_form, &rows, &cols);
        my_form_win=newwin(rows+5,MAX_NICK+20 ,5,maxx/2-(MAX_NICK+20)/2);
	
        keypad(my_form_win, TRUE);
        set_form_win(my_form, my_form_win);
        set_form_sub(my_form, derwin(my_form_win,rows,cols,4,7-(MAX_NICK/2)));
        box(my_form_win, 0, 0);
	
	print_in_middle(my_form_win, 1, 0, MAX_NICK+20,"Enter yor nick", COLOR_PAIR(2));	
	post_form(my_form);
	wrefresh(my_form_win);
	refresh();
	while((ch = wgetch(my_form_win)) != 10)
	{
	  //fprintf(stderr,"GET_NICK:ch=%d\n",ch);
		ch = nick_key_filter(ch)  ;
		switch(ch)
		{
			case KEY_BACKSPACE:
				if(pos == MAX_NICK )
					form_driver(my_form,REQ_DEL_CHAR);
				else
					{
					form_driver(my_form, REQ_LEFT_CHAR);
					form_driver(my_form, REQ_DEL_CHAR);
				}
				if ( pos != 0 )
					pos-- ; 
				break;
			case KEY_UP:
				break;
			case 0 : break ; 
			default:
				/* If this is a normal character, it gets */
				/* Printed				  */	
				form_driver(my_form, ch);
				nick[pos] = (char) ch ; 
				if(pos < MAX_NICK )
					pos ++ ; 
				break;
		}

	
	
	}

	unpost_form(my_form);
	free_form(my_form);
	free_field(field[0]);
	free_field(field[1]); 
	erase();	
	nick[MAX_NICK] = '\0';
	//fprintf(stderr,"NICK_RETURN:%s:\n",nick);	
	return nick ; 
}

void ui::print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{	
	int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}
int ui::nick_key_filter(int ch) 
{
	if (ch!=10&&ch<22||ch>33&&ch<35||ch>38&&ch<40||ch>42&&ch<48||ch>57&&ch<64||ch>90&&ch<97&&ch!=94||ch>122&&ch!=KEY_BACKSPACE)
		return 0;
	else
		return ch ;
}
	
