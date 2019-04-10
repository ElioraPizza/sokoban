#include <stdio.h>
#include <ncursesw/ncurses.h>
#include <stdlib.h>
enum {maxsize=100,testsize=10};
void getmysize (int* row,int* col,char *field)
{
								FILE *myfile=fopen("./map.txt", "r");
								char test[maxsize];
								for (int i = 0; fscanf(myfile, "%s", &field[i*maxsize])!=EOF; i++) {
																(*row)++;
								}
								for (int i = 0; field[i]!='\0'; i++)
																(*col)++;
								fclose(myfile);
}

int main ()
{
								int sizerow=0,sizecol=0;
								char field[maxsize][maxsize]={{'>'}}; /* unused char to check rewrite */
								getmysize(&sizerow,&sizecol,&field[0][0]);
								printf("%d\n%d\n",sizerow,sizecol);
								for (int i=0; i<sizerow; i++) {
																for (int j=0; j<sizecol; j++) {
																								printf("%c ",field[i][j]);
																}
																printf("\n");
								}

								// кейсы с клавишами + передвижение + сдвиг ящиков

								// game over

								// переписать поле заново
								return 0;
}
