#include <stdio.h>
#include <ncursesw/ncurses.h>
#include <stdlib.h>
// считать с файла поле
void getmysize (int* row,int* col)
{
								FILE *myfile;
								myfile=fopen("./map.txt", "r+");
								char test[40];
								fscanf(myfile, "%s", test);
								while(test[*col]!=0)
																(*col)++;
								int i;
								for (i=1; fscanf(myfile, "%s", test)!=EOF; i++);
								*row=i;
								fclose(myfile);
}
void fillfield (char* pole,int sizerow,int sizecol)
{
FILE *myfile;
myfile=fopen("./map.txt", "r+");
for(int i=0;i<sizerow;i++){

	char test[40]={';'};
	fscanf(myfile, "%s", test);

	for(int j=0;j<sizecol;j++){
		pole[ j+sizerow*i ]=test[ j ];		
	}
}
fclose(myfile);
}
int main ()
{
								int sizerow=0,sizecol=0;
								getmysize(&sizerow,&sizecol);
								printf("%d\n%d\n",sizerow,sizecol);
								char pole[sizerow][sizecol];

								fillfield(&pole[0][0],sizerow,sizecol);

								for (int i=0;i<sizerow;i++)					
									for (int j=0;j<sizerow;j++)
										printf("%c ",pole[i][j]);
								// кейсы с клавишами + передвижение + сдвиг ящиков
								
								// game over

								// переписать поле заново
								return 0;
}
