//可視化客製時鐘
#include<iostream>
#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define ANGLE M_PI/180 

SYSTEMTIME sys;

void gotoxy(int xpos, int ypos);
void printChar(int xpos, int ypos, const char* chr);
void screenUI(int width, int lengh, int shape);
void clocknum(void);
void hourhand(int hours);
void minutehand(int minutes);
void secondhand(int seconds);
int StartPoint_x;
int StartPoint_y;
int basiswidth;
int basislengh;
int basismode;
char hour[24]={
	1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,0
};
char minute[60]={
	0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59
};
char second[60]={
	0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59
};
float MajAxis;	//Major_axis
float MinAxis;	//Minor_axis

int main(void){
	std::cout<<"Enter your clock width and lengh.\n";
	std::cin>>basiswidth>>basislengh;
	std::cout<<"Choose your clock modeling.[1]rectangle [2]oval [3]Both\n";
	std::cin>>basismode;
	while(1){
		system("cls");
		screenUI(basiswidth,basislengh,basismode-1);
		clocknum();
		GetLocalTime( &sys );
		hourhand(sys.wHour);
		minutehand(sys.wMinute);
		secondhand(sys.wSecond); 
		while(sys.wMilliseconds<=980)
		{
			GetLocalTime( &sys );
		}
	}
	return 0;
}

void gotoxy(int xpos, int ypos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos+StartPoint_x;
	scrn.Y = ypos+StartPoint_y;
	SetConsoleCursorPosition(hOuput,scrn);
}

void printChar(int xpos, int ypos,const char* chr)
{
	gotoxy(xpos,ypos);
	std::cout<<chr;
}

void screenUI(int width, int lengh, int shape) 
{
	lengh = lengh/2;
	MajAxis = width/2-2;  
	MinAxis = lengh/2-2;
	StartPoint_x = (float)(width/2);
	StartPoint_y = (float)(lengh/2);
	if(shape==0){
		for(int i=0;i<width+1;i++){
			printChar(i-StartPoint_x,-StartPoint_y,"▄");
			printChar(i-StartPoint_x,lengh-1-StartPoint_y,"▄");
		} 
		for(int i=1;i<lengh;i++){
			printChar(-StartPoint_x,i-StartPoint_y,"█");
			printChar(width-StartPoint_x,i-StartPoint_y,"█");
		}
	}
	else if(shape==1){
		for(float i=-MajAxis;i<MajAxis;i+=0.1){
			printChar(i,pow(1-pow(i/MajAxis,2),0.5)*MinAxis,".");
			printChar(i,-pow(1-pow(i/MajAxis,2),0.5)*MinAxis,".");
		}
	}
	else if(shape==2){
		for(float i=-MajAxis;i<MajAxis;i+=0.1){
			printChar(i,pow(1-pow(i/MajAxis,2),0.5)*MinAxis,".");
			printChar(i,-pow(1-pow(i/MajAxis,2),0.5)*MinAxis,".");
		}
		for(int i=0;i<width+1;i++){
			printChar(i-StartPoint_x,-StartPoint_y,"▄");
			printChar(i-StartPoint_x,lengh-1-StartPoint_y,"▄");
		} 
		for(int i=1;i<lengh;i++){
			printChar(-StartPoint_x,i-StartPoint_y,"█");
			printChar(width-StartPoint_x,i-StartPoint_y,"█");
		}
	}
	else return;
} 

void clocknum(void){
	printChar(	MajAxis*cos(ANGLE*(270+30*1)),	MinAxis*sin(ANGLE*(270+30*1)),"１");
	printChar(	MajAxis*cos(ANGLE*(270+30*2)),	MinAxis*sin(ANGLE*(270+30*2)),"２");
	printChar(	MajAxis*cos(ANGLE*(270+30*3)),	MinAxis*sin(ANGLE*(270+30*3)),"３");
	printChar(	MajAxis*cos(ANGLE*(270+30*4)),	MinAxis*sin(ANGLE*(270+30*4)),"４");
	printChar(	MajAxis*cos(ANGLE*(270+30*5)),	MinAxis*sin(ANGLE*(270+30*5)),"５");
	printChar(	MajAxis*cos(ANGLE*(270+30*6)),	MinAxis*sin(ANGLE*(270+30*6)),"６");
	printChar(	MajAxis*cos(ANGLE*(270+30*7)),	MinAxis*sin(ANGLE*(270+30*7)),"７");
	printChar(	MajAxis*cos(ANGLE*(270+30*8)),	MinAxis*sin(ANGLE*(270+30*8)),"８");
	printChar(	MajAxis*cos(ANGLE*(270+30*9)),	MinAxis*sin(ANGLE*(270+30*9)),"９");
	printChar(	MajAxis*cos(ANGLE*(270+30*10)),	MinAxis*sin(ANGLE*(270+30*10)),"１０");
	printChar(	MajAxis*cos(ANGLE*(270+30*11)),	MinAxis*sin(ANGLE*(270+30*11)),"１１");
	printChar(	MajAxis*cos(ANGLE*(270+30*12)),	MinAxis*sin(ANGLE*(270+30*12)),"１２");
}

void hourhand(int hours)
{
	float R = pow(pow(MajAxis,2)+pow(MinAxis,2),0.5);
	char chr[10+sizeof(char)];
	sprintf(chr,"%d",hour[hours-1]);
	for(float i=0;i<R*0.6;i+=2){
		printChar((i/R)*MajAxis*cos(ANGLE*(270+30*hours+0.5*sys.wMinute)),(i/R)*MinAxis*sin(ANGLE*(270+30*hours+0.5*sys.wMinute)),chr);
	} 
}

void minutehand(int minutes)
{
	float R = pow(pow(MajAxis,2)+pow(MinAxis,2),0.5);
	char chr[10+sizeof(char)];
	sprintf(chr,"%d",minute[minutes]);
	for(float i=0;i<R*0.75;i+=2){
		printChar((i/R)*MajAxis*cos(ANGLE*(270+6*minutes)),(i/R)*MinAxis*sin(ANGLE*(270+6*minutes)),chr);
	}
}

void secondhand(int seconds)
{
	float R = pow(pow(MajAxis,2)+pow(MinAxis,2),0.5);
	char chr[10+sizeof(char)];
	sprintf(chr,"%d",second[seconds]);
	for(float i=0;i<R*0.9;i+=2){
		printChar((i/R)*MajAxis*cos(ANGLE*(270+6*seconds)),(i/R)*MinAxis*sin(ANGLE*(270+6*seconds)),chr);
	}
}
