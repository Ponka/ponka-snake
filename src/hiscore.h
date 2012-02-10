#ifndef __HISCORE_H__
#define __HISCORE_H__

/* TODO - pobranie katalogu domowego przez >getenv();< */
#define SAVE_FILE ".jkl_snake"
#include<stdio.h>				
#include<string.h>

#include<stdlib.h>			
/* rekordzisci .. klasa `hiscores' */
#define MAX_HISCORE	10
#define MAX_NICK	3


/*
 * struktura :
 * 	- > hiscore_s < - przechowuje jeden wpis do tablicy wynikow.
 */ 
//struct hiscore_s
struct Score
{
	int score;
	char *nick;
	Score(){ nick = new char [MAX_NICK+1];
	         strcpy(nick,"AAA");
		 //fprintf(stderr,"KONSTRUKTOR.nick = %s\n",nick); 
	}
	~Score(){ delete [] nick ; } 

};
//typedef struct hiscore_s Score;


/*
 *	KLASA :
 * 	       
 * 	  XXX	>> hiscore <<	XXX - obsluga tablicy najlepszych wynikow.
 */
class hiscore
{
	public:
		/* konstruktor wczytuje wyniki z pliku */
		/* TODO - przeciazony konstruktor narzucajacy scierzke do */
		/*	pliku z najlepszymi wynikami */
		hiscore();
		~hiscore();
		int chk_if_good(int score);//1 -  podaj nicka;0-odbierz liste
		Score *get_list(char *nick); // po tym pobierz liste.
		Score *get_list();
		void print_list(void);
	private:
		Score *list ;
		char *path;
		int tmp_score;
		void sort_list();
//		void sort_list_AYss()
		char *nick;	
		void load();
		void save();
};		

#endif /* __HISCORE_H__ */
