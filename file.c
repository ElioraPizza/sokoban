#include <stdio.h>
#include <ncursesw/ncurses.h>
#include <stdlib.h>
#define error_mes The number of boxes is not \
								equal to the number of goals, the game is impossible.
enum {maxsize=100,testsize=10};
enum {W_key=119,A_key=97,S_key=115,D_key=100};
char* getmysize (int* row,int* col)
{
								FILE *myfile=fopen("./map.txt", "r");
								char a;
								char* field=(char*)malloc(1);
								int i=0;
								(*row)=1;
								do {

																(*col)++;
																a=fgetc(myfile);
																field=(char*)realloc(field,*col);
																field[i]=a;
																i++;
								} while(a!='\n');
								i--;
								(*col)--;
								field=(char*)realloc(field,*col);
								int nexts=(*col)*2;
								while(a!=EOF) {
																field=(char*)realloc(field,nexts);
																for (int j=0; j<*col && a!=EOF; j++) {
																								a=fgetc(myfile);
																								field[i]=a;
																								i++;
																}
																(*row)++;
																a=fgetc(myfile);
																nexts+=*col;
								}
								(*row)--;
								nexts-=*col+*col;
								field=(char*)realloc(field,nexts);
								fclose(myfile);
								return field;
}
void myscreen(int row, int col, char (*field)[col])
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
int findmychar(int row, int col, char (*field)[col],int *coordch,
															int *boxcount,int (*xbox)[2]) /* int (*box)[2] */
{
								int test=0;
								for (int i=0; i<row; i++)
																for (int j=0; j<col; j++)
																								if (field[i][j]=='c') {
																																coordch[0]=i;
																																coordch[1]=j;
																								} else if (field[i][j]=='b') {
																																/*		box[*boxcount][0]=i;
																																   box[*boxcount][1]=j; */
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
void goingthings(int cols,int row,int col,char (*field)[cols],int *ch,
																	int (*xbox)[2],int boxcount) /* int (*box)[2] */
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
																/*	for (int i=0; i<boxcount; i++)
																         if (box[i][0] == ch[0]+row && box[i][1] == ch[1]+col) {
																                 box[i][0]+=row;
																                 box[i][1]+=col;
																                 break;
																         } */
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
																field[ch[0]][ch[1]]='-';
																ch[0]+=row;
																ch[1]+=col;
																break;
								}
								for (int i=0; i<boxcount; i++)
																if (field[ xbox[i][0] ][ xbox[i][1] ] == '-') {
																								field[ xbox[i][0] ][ xbox[i][1] ]='x';
																}
}
bool gameovertest(int col,int drow,int dcol,char (*field)[col],int xbox[][2],int boxcount)
{
								int doneboxes=0;
								for (int i = 0; i < boxcount; i++) {
																if (field[xbox[i][0]][xbox[i][1]]=='b') doneboxes++;
								}
								if (doneboxes== boxcount) {
																printw("Map passed. Press F to pay respect.\n");
																refresh();
																char f;
																do {
																								scanf("%c",&f);
																} while(f!='F');
																return true;
								}
								/* for (int i=0; i<drow; i++) {
								        for (int j=0; j<dcol; j++) {
								                int u=0,d=0,l=0,r=0;
								                if (field[i][j]=='b') {
								                        if (field[i-1][j]=='w') u=1;
								                        if (field[i+1][j]=='w') d=1;
								                        if (field[i][j-1]=='w') l=1;
								                        if (field[i][j+1]=='w') r=1;
								                        switch (u+d+l+r) {
								                        case 1:
								                                break;
								                        default: ;
								                                bool tester=true;
								                                for (int k=0; i<boxcount; i++)
								                                        if (i == xbox[k][0] && j== xbox[k][1])
								                                                tester=false;
								                                if (tester) {
								                                        printw("You lose. Press F to pay respect\n");
								                                        refresh();
								                                        char f;
								                                        do {
								                                                scanf("%c",&f);
								                                        } while(f!='F');
								                                        return true;
								                                }
								                                break;
								                        }
								                }
								        }
								   } */

								return false;
}
int main ()

{
								initscr();
								int error;
								int sizerow=0,sizecol=0;
								/* char field[maxsize][maxsize]={{'>'}}; */
								/* unused char to check rewrite */
								int coordch[2];
								/* int box[maxsize][2]={{-1}}; */
								int boxcount=0;
								int xbox[maxsize][2]={{-1}};
								char (*field)[sizecol]=getmysize(&sizerow,&sizecol);
								myscreen(sizerow,sizecol,field);

								error=findmychar(sizerow,sizecol,field,coordch,
																									&boxcount,xbox); /* box */
								if (error) return 0;

								int drow=-1,dcol=0;
								bool result;

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
																goingthings(sizecol,drow,dcol,field,coordch,xbox,boxcount); /* box */

																clear();

																result=gameovertest(sizecol,drow,dcol,field,xbox,boxcount);
																if (result) break;

																myscreen(sizerow,sizecol,field);
								}
								endwin();
								return 0;
}
