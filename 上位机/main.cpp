#include"GuiMusicPlayer.h"
#include"WZSerialPort.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
//#include<WinSock2.h>
#include<windows.h>
#include<iostream>
#include<graphics.h>
#include <conio.h>
#pragma comment(lib,"Winmm.lib")
using namespace std;
WZSerialPort w;
string data1;
int volume = 50;
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	w.open("\\\\.\\com7", 9600, 0, 8, 1, 1);
	GuiMusicPlayer& gmp = GuiMusicPlayer::singleton();
	gmp.run();
	return 0;
}