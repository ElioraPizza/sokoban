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
int main ()
{
								int sizerow=0,sizecol=0;
								getmysize(&sizerow,&sizecol);
								printf("%d\n%d\n",sizecol,sizerow);
								// кейсы с клавишами + передвижение + сдвиг ящиков

								// game over

								// переписать поле заново
								return 0;
}
