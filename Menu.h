#pragma once
//#include <iostream>
#include <conio.h>
//#include <windows.h>
#include <string>
#include <stack>
#include "MyQueue.h"
#include "Bitmap.h"
#include "QrCode.h"
#define ITALICS "\033[3m"
#define UNDERLINE "\033[4m"
#define BOLD "\033[1m"
#define DEFAULT "\033[0m"
#define IUB ITALICS UNDERLINE BOLD
//*******************PSEUDOGRAPHICS***********************
#define VERT_1 179
#define VERT_2 186
#define VERT_2_LEFT_1 182
#define VERT_2_RIGHT_1 199
#define HORIZ_1 196
#define HORIZ_2 205
#define HORIZ_2_UP_1 207
#define HORIZ_2_DOWN_1 209
#define CROSS_1 197
#define UP_RIGHT_2 201
#define UP_LEFT_2 187
#define DOWN_RIGHT_2 200
#define DOWN_LEFT_2 188
#define BLOCK 219
#define SQUARE 254
#define REMOVE INT_MIN
#define RETURN INT_MAX
//*******************KEY_CODE*****************************
#define KEY_ESCAPE 27
#define KEY_ENTER 13
#define KEY_BACKSPACE 8
#define KEY_PG_UP 72
#define KEY_PG_DOWN 80
#define KEY_PG_RIGHT 77
#define KEY_PG_LEFT 75
class Menu
{
private:
	MyQueue<std::string> text;
	std:: fstream txt_file;
	std:: stack<std::string> removing;
public:
	int interaction_menu(int* option, int max);
	void menu();
	void frame(int pos, int max, int length_txt);
	int print_menu(bool allow_editing, const std::string path);
	void set_text(std::string path);
	int max_length();
	void about();
	void rreturn_to(const std::string path);
	void add(std::string filename);
};

