#include <stdio.h>
#include <ncursesw/ncurses.h>
#include <stdlib.h>
#define error_mes The number of boxes is not \
								equal to the number of goals, the game is impossible.
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
																																printw("  "); /* Nothing */
																																break;
																								}
																printw("\n");
								}
}
int findmychar(int row, int col, char (*field)[maxsize],int *coordch,
															int (*box)[2],int *boxcount,int (*xbox)[2])
{
								int test=0;
								for (int i=0; i<row; i++)
																for (int j=0; j<col; j++)
																								if (field[i][j]=='c') {
																																coordch[0]=i;
																																coordch[1]=j;
																								} else if (field[i][j]=='b') {
																																box[*boxcount][0]=i;
																																box[*boxcount][1]=j;
																																(*boxcount)++;

																								} else if (field[i][j]=='x') {
																																xbox[test][0]=i;
																																xbox[test][1]=j;
																																test++;
																								}

								if (test!=*boxcount) {
																printw("error_mes");
																/* need usleep or something here */
																return 1;
								}
								return 0;
}
void goingthings(int row,int col,char (*field)[maxsize],int *ch,
																	int (*xbox)[2],int boxcount)
{
								switch (field[ch[0]+row][ch[1]+col]) {
								case 'w':

																break;
								case 'b':
																if (field[ch[0]+row*2][ch[1]+col*2]=='b' ||
																				field[ch[0]+row*2][ch[1]+col*2]=='w') break;

																field[ch[0]+row*2][ch[1]+col*2]='b';
																field[ch[0]+row][ch[1]+col]='c';
																field[ch[0]][ch[1]]='-';
																for (int i=0; i<boxcount; i++)
																								if (xbox[i][0] == ch[0]+row && xbox[i][1] == ch[1]+col) {
																																xbox[i][0]+=row;
																																xbox[i][1]+=col;
																																break;
																								}
																ch[0]+=row;
																ch[1]+=col;
																break;
								case 'x':
																field[ch[0]+row][ch[1]+col]='c';
																field[ch[0]][ch[1]]='-';
																ch[0]+=row;
																ch[1]+=col;
																break;
								case '-':
																field[ch[0]+row][ch[1]+col]='c';
																bool writex=false;
																for (int i=0; i<boxcount; i++)
																								if (xbox[i][0] == ch[0] && xbox[i][1] == ch[1])
																																writex=true;

																if (writex) field[ch[0]][ch[1]]='x';
																else field[ch[0]][ch[1]]='-';
																ch[0]+=row;
																ch[1]+=col;
																break;
								}
								for (int i=0; i<boxcount; i++)
																if (field[ xbox[i][0] ][ xbox[i][1] ] == '-') {
																	field[ xbox[i][0] ][ xbox[i][1] ]='x';
																}
}
int main ()
{
								initscr();
								int error;
								int sizerow=0,sizecol=0;
								char field[maxsize][maxsize]={{'>'}}; /* unused char to check rewrite */
								int coordch[2];
								int box[maxsize][2]={{-1}}, boxcount=0;
								int xbox[maxsize][2]={{-1}};

								getmysize(&sizerow,&sizecol,&field[0][0]);

								myscreen(sizerow,sizecol,field);

								error=findmychar(sizerow,sizecol,field,coordch,
																									box,&boxcount,xbox);
								if (error) return 0;

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
																								dcol=1;
																								break;
																}
																goingthings(drow,dcol,field,coordch,xbox,boxcount);

																clear();

																/* gameovertest(boxcount,box,field); */

																myscreen(sizerow,sizecol,field);
								}
								return 0;
}
