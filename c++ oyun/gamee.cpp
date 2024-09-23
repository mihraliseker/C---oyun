#include<iostream>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<thread>
#include<chrono>
#include<time.h>
#define YUKARI 72
#define ASAGI 80
#define SAG 77
#define SOL 75
#define DIKEY 20
#define YATAY 79
#define SPACE 32
#define ESC 27
using namespace std;

int satir,sutun,x,karx=2,kary=16,i,j,cizx,cizy,tus,tussayac;
int d1x=25,d1y=15,d2x=35,d2y=5,d3x=48,d3y=2;
int bulletsx[10],sayac,gemidurum[1500],bulletsy[10];
int d1mesafe=0,d2mesafe=0,d3mesafe=0;
char alan[DIKEY+2][YATAY];
void gotoxy(int x,int y);
bool d1bool=true,d2bool=true,d3bool=true;
char d1s='&',d2s='+',d3s='*';

void dusmansil(char smg);
void gotoxy(int x, int y)
{
	COORD Pos = {x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Pos);
}
void hidecursor(){
	CONSOLE_CURSOR_INFO cursor_info={1,0}; 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);	
}


void enemy(int ddurum,int &dx,int &dy,int &mesafe,char smg,bool cntrl){ 
	if(cntrl)
   		switch(ddurum)
   		{
   			case 1:
   			    if(dx-1>0){
	   				alan[dy][--dx]=smg;
	   				alan[dy][dx+1]=' ';
	   				if(alan[dy][dx]==alan[kary][karx])
	   				{
	   				   gotoxy(45,22);
	   				   cout<<"Oyunu Kaybettin!";
	   			       exit(0);
	   				}
	   			}
	   			else
	   			mesafe=0;
   				break;
   			case 2:
  				if(dx+1<YATAY-1){
	   				alan[dy][++dx]=smg;
	   				alan[dy][dx-1]=' ';
	   				if(alan[dy][dx]==alan[kary][karx])
	   				{
	   				   gotoxy(45,22);
	   				   cout<<"Oyunu Kaybettin!";
	   			       exit(0);
	   				}
	   			}
	   			else
	   			mesafe=0;
   				break;
   			case 3:
   				if(dy-1>0)  {
   					alan[--dy][dx]=smg;
   					alan[dy+1][dx]=' ';
   					if(alan[dy][dx]==alan[kary][karx])
	   				{
	   				   gotoxy(45,22);
	   				   cout<<"Oyunu Kaybettin!";
	   			       exit(0);
	   				}
   				}
   				else
	   			mesafe=0;
   				break;
   			case 4:
   				if(dy+1<DIKEY){
	   				alan[++dy][dx]=smg;
	   				alan[dy-1][dx]=' ';
	   				if(alan[dy][dx]==alan[kary][karx])
	   				{
	   				   gotoxy(45,22);
	   				   cout<<"Oyunu Kaybettin!";
	   			       exit(0);
	   				}
	   			}
	   			else
	   			mesafe=0;
   				break;
   		}
}

void d1(){
	srand(time(NULL));
	int d1durum=rand()%4+1;
	d1mesafe=1+rand()%45;
	for(int konumgit1=0;konumgit1<d1mesafe;konumgit1++){
		enemy(d1durum,d1x,d1y,d1mesafe,d1s,d1bool);
		Sleep(200);
	}
	if(d1bool)
	d1();
}

void d2(){
	srand(time(NULL));
	int d2durum=rand()%4+1;
	d2durum=rand()%4+1;
	d2mesafe=1+rand()%50;
	for(int konumgit2=0;konumgit2<d2mesafe;konumgit2++){         
		enemy(d2durum,d2x,d2y,d2mesafe,d2s,d2bool);
		Sleep(200);
	}
	if(d2bool)
	d2();
}

void d3(){
	srand(time(NULL));
	int d3durum=rand()%4+1;
	d3durum=rand()%4+1;
	d3durum=rand()%4+1;
	d3mesafe=1+rand()%55;
	for(int konumgit3=0;konumgit3<d3mesafe;konumgit3++){
		enemy(d3durum,d3x,d3y,d3mesafe,d3s,d3bool);
		Sleep(200);
	}
	if(d3bool)
	d3();
}

void dusmansil(char smg)
{
	for(int cizx=0;cizx<DIKEY+2;cizx++){
    	for(int cizy=0;cizy<YATAY;cizy++){
    		if(alan[cizx][cizy]==smg)
    		alan[cizx][cizy]=' ';
    	}
    }
}

void kontrol(int x,int y);

class bullet{
	public:
		bullet(int x,int y){
			bulletsx[sayac]=x;
			bulletsy[sayac]=y;
			switch(gemidurum[tussayac-1])
			{
			case SAG:
			++sayac;
			for(int a=bulletsx[sayac-1]+2;a<YATAY-1;a++){
				alan[y][a]='-';
				alan[y][a-1]=' ';
				
				this_thread::sleep_for(chrono::milliseconds(100));
				if(a==YATAY-2)
				alan[y][a]=' ';
				kontrol(a+1,y);
			}
			--sayac;
		
			break;
			case SOL:
			++sayac;
			for(int a=bulletsx[sayac-1]-2;a>0;a--){
				alan[y][a]='-';
				alan[y][a+1]=' ';
				this_thread::sleep_for(chrono::milliseconds(100));
				if(a==1)
				alan[y][a]=' ';
				kontrol(a-1,y);
			}
			--sayac;
		
			break;
			case YUKARI:
			++sayac;
			for(int a=bulletsy[sayac-1]-2;a>0;a--){
				alan[a][x]='-';
				alan[a+1][x]=' ';
				this_thread::sleep_for(chrono::milliseconds(100));
				if(a==1)
				alan[a][x]=' ';
				kontrol(x,a-1);
			}
			--sayac;
			
			break;
			case ASAGI:
			++sayac;
			for(int a=bulletsy[sayac-1]+2;a<DIKEY;a++){
				alan[a][x]='-';
				alan[a-1][x]=' ';
				this_thread::sleep_for(chrono::milliseconds(100));
				if(a==DIKEY-1)
				alan[a][x]=' ';
				kontrol(x,a+1);
			}
			--sayac;
			break;
		}
		delete this;
	}
};


void kontrol(int x,int y){
	switch(alan[y][x])
	{
		case '&':
			alan[y][x]=' ';
			d1bool=false;
			break;
		case '+':
			alan[y][x]=' ';
			d2bool=false;
			break;
		case '*':
			alan[y][x]=' ';
			d3bool=false;
			break;
	}
}

void fire(){
	bullet *m=new bullet(karx,kary);
}

void arrayciz(){
	gotoxy(0,0);
    for(int cizx=0;cizx<DIKEY+2;cizx++){
    	for(int cizy=0;cizy<YATAY;cizy++){
    		cout<<alan[cizx][cizy];
    	}
    	cout<<endl;
    }
}
	              
void arrayolustur(){          
	for(i=0;i<YATAY+1;i++){
		if(i==0){
			alan[0][i]=201;
		}
		else if(i==YATAY-1){
			alan[0][i]=187;
		}else{
			alan[0][i]=205;
		}
		}

	cout<<endl;
		for( i=1;i<DIKEY;i++){
			alan[i][0]=186;	
			for(j=1;j<=YATAY;j++){
			if(j==YATAY-1){
			alan[i][j]=186;
		    }
			else{	
			alan[i][j]=32;				
			}
		}
		cout<<endl;
	}
	for(i=0;i<YATAY;i++){
		if(i==0){
			alan[DIKEY][i]=200;
		}
		else if(i==YATAY-1){
			alan[DIKEY][i]=188;
		}
		else{
			alan[DIKEY][i]=205;
		}
	}
}

void hareket()
{
	gotoxy(karx,kary);
	cout<<">";
	hidecursor();
	do{
		if(kbhit())
		{
	 	tus = getch();
		if(tus!=32)
	 	{
	 	gemidurum[tussayac]=tus;
	 	tussayac++;
 		}
	 	switch(tus)
	 	{
	 	 case ASAGI:
	 	 if(kary+1!=DIKEY)
	 	 {
	     alan[++kary][karx]='v';
	     alan[kary-1][karx]=' ';
	     }
	 	break;
	 	case YUKARI:
		 if(kary-1!=0)
		 {
	     alan[--kary][karx]='^';
	     alan[kary+1][karx]=' ';
	     }
	 	 break;	
	 	case SOL:
	 	 if(karx-1!=0){
	     alan[kary][--karx]='<';
	     alan[kary][karx+1]=' ';
	 	 }
	 	 break;
	 	case SAG:
	 	 if(karx+1!=YATAY)
	 	 {
	     alan[kary][++karx]='>';
	     alan[kary][karx-1]=' ';
	 	 }
	 	 break;
	 	 case SPACE:
	 	 	if(sayac<10)
	 	 	{
	 	 	thread t2(&fire);
	 	 	t2.detach();
	 	 	}
	 	 break;
	    }
	}
	gotoxy(0,0);
	arrayciz();

	 for(int sa=0;sa<10-sayac;sa++)
	 {
	 cout<<" "<<'|';
	 }
	 cout<<"               "<<endl;
	 cout<<"Dusman1="<<d1bool<<endl;
	 cout<<"Dusman2="<<d2bool<<endl;
	 cout<<"Dusman3="<<d3bool<<endl;
	 hidecursor();
	if(d1bool==false && d2bool==false && d3bool==false){
		gotoxy(40,21);
		cout<<"Oyunu Kazandin!";
		exit(0);
	}
	}while(tus!=ESC); 
}

int main(){
   hidecursor();
   arrayolustur();
   thread one(&d1);
   one.detach();
   thread two(&d2);
   two.detach();
   thread three(&d3);
   three.detach();
   hareket();	
}
