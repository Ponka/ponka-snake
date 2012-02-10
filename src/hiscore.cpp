



#include"hiscore.h"

hiscore::hiscore()
{
	load();
}
hiscore::~hiscore()
{
	save();
	free(path);
	free(list);
}
void hiscore::load()
{
	char *homedir; 
	int i ;
	FILE *f ;
	size_t ret ;
	homedir = getenv("HOME");	
	path = (char*)malloc(strlen(SAVE_FILE) + strlen(homedir)+1) ; 
	path = strcpy(path,homedir);
	path = strcpy(path,SAVE_FILE);
	
	if((f = fopen(path, "r")) == NULL )
	{
		f = fopen(path, "a+"); // bardzo to brzydkie ... FIXME 
		fclose(f);
		f = fopen(path, "r");
	}
	list = new Score[MAX_HISCORE];
	for ( i = 0; i < MAX_HISCORE ; i++ ) 
	{	
		ret = fread((void*) &(list[i].score),sizeof(int),1, f) ;
		ret = fread((void*) list[i].nick ,sizeof(char),MAX_NICK+1,f);
		//fprintf(stderr,"LOAD:i:%d:score:%d:nick:%s:\n",i,list[i].score,list[i].nick);

	}
	fclose(f);
}
void hiscore::save()
{
	FILE *f ;
	size_t ret ;
	int i ;	
	if((f = fopen(path, "w")) == NULL)
	{
	  //fprintf(stderr,"fopen(%s)@hiscore::load()\n",path);
		exit(1);
	}
	for ( i = 0; i < MAX_HISCORE ; i++ ) 
	{
	  //fprintf(stderr,"SAVE:i:%d:score:%d:nick:%s:\n",i,list[i].score,list[i].nick);
		ret = fwrite((void*) &(list[i].score),sizeof(int),1, f) ;
		ret = fwrite((void*) list[i].nick ,sizeof(char),MAX_NICK+1,f);
	}
//	ret = fwrite((void*)list,sizeof(Score),(size_t)MAX_HISCORE,f);
	fflush(f);
	fclose(f);
}
Score *hiscore::get_list(char *nick) 
{
	int i  ;
	//fprintf(stderr,"GET_LIST:list-ostatni.nick = %3s \n",list[MAX_HISCORE -1].nick);
	strcpy(list[MAX_HISCORE- 1].nick , nick) ;
	list[MAX_HISCORE - 1].score = tmp_score;
	for ( i = 0; i < MAX_HISCORE ; i++ ) 
	{
	  //fprintf(stderr,"GET_LIST:B_SORT:i:%d:score:%d:nick:%s:\n",i,list[i].score,list[i].nick);
	}

	sort_list();
	for ( i = 0; i < MAX_HISCORE ; i++ ) 
	{
	  //fprintf(stderr,"GET_LIST:A_SORT:i:%d:score:%d:nick:%s:\n",i,list[i].score,list[i].nick);
	}
	return list ; 
}
Score *hiscore::get_list()
{
	return list ;

}/*
void hiscore::sort_list()
{
	int i,j ;
	Score tmp;
	for( i = 0 ; i < MAX_HISCORE ; i++ )
		for( j = MAX_HISCORE -1  ; j > i ; j--)
			if (list[j].score > list[j-1].score)
			{
				tmp = list[j-1] ;
				list[j-1] = list[j];
				list[j] = tmp;

//fprintf(stderr,"SORT:tmp.nick:%s:list[%d].nick:%s:list[%d].nick:%s:\n",tmp.nick,j,list[j].nick,j-1,list[j-1].nick);
	}
}*/

void hiscore::sort_list()
{
	int i = 0;
	bool posortowano = false;
	char tmpstr[4] = {0};
	int tmpint = 0;

	do
	{
		posortowano = true;
		for ( i = 0; i < (MAX_HISCORE - 1); i++){
			if (list[i].score < list[i + 1].score){
				strcpy(tmpstr, list[i].nick);
				tmpint = list[i].score;
				strcpy(list[i].nick, list[i + 1].nick);
				list[i].score = list[i + 1].score;
				strcpy(list[i + 1].nick, tmpstr);
				list[i + 1].score = tmpint;
				posortowano = false;
			}
		}
	} while (!posortowano);
}
	



int hiscore::chk_if_good(int score)
{
	if(score > list[MAX_HISCORE - 1].score)
	{
		tmp_score = score ;	
		return 1 ;	
	}
	else
		return 0;
}	
	


