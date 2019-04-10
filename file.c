#include <stdio.h>
#include <ncursesw/ncurses.h>
#include <stdlib.h>
enum {maxsize=100,testsize=10};
enum {W_key=119,A_key=97,S_key=115,D_key=100};
void getmysize (int* row,int* col,char *field)
{
								FILE *myfile=fopen("./map.txt", "r");
								for (int i = 0; fscanf(myfile, "%s", &field[i*maxsize])!=EOF; i++) {
																(*row)++;
								}
								for (int i = 0; field[i]!='\0'; i++)
																(*col)++;
								fclose(myfile);
}
void myscreen(int row, int col, char (*field)[maxsize])
{
								for (int i=0; i<row; i++) {
																for (int j=0; j<col; j++)
																								switch(field[i][j]) {
																								case 'w':
																																printw("- "); /* Wall */
																																break;
																								case 'c':
																																printw("c "); /* Character */
																																break;
																								case 'b':
																																printw("+ "); /* Box */
																																break;
																								case 'x':
																																printw("x "); /* Target */
																																break;
																								case '-':
																																printw("  ");         /* Nothing */
																																break;
																								}
																printw("\n");
								}
}
void findmychar(int row, int col, char (*field)[maxsize],int *coordch,int (*box)[2],int *boxcount)
{
								for (int i=0; i<row; i++)
																for (int j=0; j<col; j++)
																								if (field[i][j]=='c') {
																																coordch[0]=i;
																																coordch[1]=j;
																								} else if (field[i][j]=='b') {
																																box[*boxcount][0]=i;
																																box[*boxcount][1]=j;
																																(*boxcount)++;

																								}
}
int main ()
{
								initscr();
								int sizerow=0,sizecol=0;
								char field[maxsize][maxsize]={{'>'}}; /* unused char to check rewrite */
								int coordch[2];
								int box[maxsize][2]={{-1}}, boxcount=0;

								getmysize(&sizerow,&sizecol,&field[0][0]);

								myscreen(sizerow,sizecol,field);

								findmychar(sizerow,sizecol,field,coordch,box,&boxcount);

								printw("%d %d\n",coordch[0],coordch[1]);
								int drow=-1,dcol=0;

								while (true)
								{
																refresh();
																switch ( getch() ) {
																case W_key:
																								drow=-1;
																								dcol=0;
																								break;
																case S_key:
																								drow=1;
																								dcol=0;
																								break;
																case A_key:
																								drow=0;
																								dcol=-1;
																								break;
																case D_key:
																								drow=0;
																								dcol=-1;
																								break;
																case ERR:
																								break;
																}

																clear();
																
																myscreen(sizerow,sizecol,field);
								}

								// кейсы с клавишами + передвижение + сдвиг ящиков

								// game over

								// переписать поле заново
								return 0;
}
