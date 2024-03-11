#include <graphics.h>
#include "Button.h"
#include <string>
#include <windows.h>
Button::Button(int x, int y, int w, int h, char text[])
{
	this->w = w;
	this->h = h;
	this->x = x;
	this->y = y;
	strcpy(this->text, text);
	this->init();
}

void Button::change()
{
	setbkmode(TRANSPARENT);
	setfillcolor(RED);
	fillroundrect(x, y, x + w, y + h, 10, 10);
	char s1[] = "Arial BLACK";
	settextstyle(88, 0, s1);
	settextcolor(WHITE);

	int tx = x + (w - textwidth(text)) / 2;
	int ty = y + (h - textheight(text)) / 2;

	outtextxy(tx, ty, text);
}

void Button::init()
{
	this->w = w;
	this->h = h;
	this->x = x;
	this->y = y;
	strcpy(this->text, text);
	setbkmode(TRANSPARENT);
	setfillcolor(RGB(192, 192, 192));
	fillroundrect(x, y, x + w, y + h, 10, 10);
	char s1[] = "Arial BLACK";
	settextstyle(88, 0, s1);
	settextcolor(BLACK);

	int tx = x + (w - textwidth(text)) / 2;
	int ty = y + (h - textheight(text)) / 2;

	outtextxy(tx, ty, text);
}
