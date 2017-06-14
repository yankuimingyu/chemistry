#ifndef _NANJING_H
#define _NANJING_H	
#include "sys.h"
#include "WM.h"
#include "GUI.h"
#include "DIALOG.h"
//#include "chinese_charcter.c"
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//ADC 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/7
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

WM_HWIN CreateNANJING(void);
static void _UserDraw(WM_HWIN hWin, int Stage);
static void _AddValues(void);

void _sinx(int i);
void _Beep(void);

	static GUI_CONST_STORAGE GUI_COLOR _aColorsArrow[] = {
		0xFFFFFF, 0x000000
};

static GUI_CONST_STORAGE GUI_LOGPALETTE _PalArrow = {
	2,	/* number of entries */
	1, 	/* No transparency */
	&_aColorsArrow[0]
};

static GUI_CONST_STORAGE unsigned char _acArrowRight[] = {
	____XX__, ________,
	____XXXX, ________,
	XXXXXXXX, XX______,
	____XXXX, ________,
	____XX__, ________
};

static GUI_CONST_STORAGE unsigned char _acArrowLeft[] = {
	____XX__, ________,
	__XXXX__, ________,
	XXXXXXXX, XX______,
	__XXXX__, ________,
	____XX__, ________
};

static GUI_CONST_STORAGE GUI_BITMAP _bmArrowRight = {
	10,            /* XSize */
	5,             /* YSize */
	2,             /* BytesPerLine */
	1,             /* BitsPerPixel */
	_acArrowRight, /* Pointer to picture data (indices) */
	&_PalArrow     /* Pointer to palette */
};

static GUI_CONST_STORAGE GUI_BITMAP _bmArrowLeft = {
	10,            /* XSize */
	5,             /* YSize */
	2,             /* BytesPerLine */
	1,             /* BitsPerPixel */
	_acArrowLeft,  /* Pointer to picture data (indices) */
	&_PalArrow     /* Pointer to palette */
};
//
// Array of keys
//
static int _aKey[] = {GUI_KEY_DELETE, GUI_KEY_TAB, GUI_KEY_LEFT, GUI_KEY_RIGHT};

//
// Dialog resource of numpad

//键盘
static const GUI_WIDGET_CREATE_INFO _aDialogNumPad[] = {//按键太多要消除一些
	//
	//  Function                 Text      Id                 Px   Py   Dx   Dy
	//
	{ WINDOW_CreateIndirect,   0,        0,                225, 110,  150, 200},
	{ BUTTON_CreateIndirect,   "7",      GUI_ID_USER +  7+50,   5,   5,  50,  20},
	{ BUTTON_CreateIndirect,   "8",      GUI_ID_USER +  8+50,  35,   5,  50,  20},
	{ BUTTON_CreateIndirect,   "9",      GUI_ID_USER +  9+50,  65,   5,  50,  20},
	{ BUTTON_CreateIndirect,   "4",      GUI_ID_USER +  4+50,   5,  30,  25,  20},
	{ BUTTON_CreateIndirect,   "5",      GUI_ID_USER +  5+50,  35,  30,  25,  20},
	{ BUTTON_CreateIndirect,   "6",      GUI_ID_USER +  6+50,  65,  30,  25,  20},
	{ BUTTON_CreateIndirect,   "1",      GUI_ID_USER +  1+50,   5,  55,  25,  20},
	{ BUTTON_CreateIndirect,   "2",      GUI_ID_USER +  2+50,  35,  55,  25,  20},
	{ BUTTON_CreateIndirect,   "3",      GUI_ID_USER +  3+50,  65,  55,  25,  20},
	{ BUTTON_CreateIndirect,   "0",      GUI_ID_USER +  0+50,   5,  80,  25,  20},
	{ BUTTON_CreateIndirect,   "T",      GUI_ID_USER +  15+50,   5,  80,  25,  20},
	{ BUTTON_CreateIndirect,   ".",      GUI_ID_USER + 10+50,  35,  80,  25,  20},
	{ BUTTON_CreateIndirect,   "Del",    GUI_ID_USER + 11+50,  65,  80,  25,  20},
	{ BUTTON_CreateIndirect,   "Tab",    GUI_ID_USER + 12+50,   5, 105,  25,  20},
	{ BUTTON_CreateIndirect,   0,        GUI_ID_USER + 13+50,  35, 105,  25,  20},
	{ BUTTON_CreateIndirect,   0,        GUI_ID_USER + 14+50,  65, 105,  25,  20},
};
/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
///
static void _cbDialogNumPad(WM_MESSAGE * pMsg) {
	GUI_RECT r;
	unsigned i; 
	int      NCode;
	unsigned Id;
	int      Pressed;
	WM_HWIN  hDlg;
	WM_HWIN  hItem;

	Pressed = 0;
	hDlg = pMsg->hWin;
	switch (pMsg->MsgId) {
	case WM_PAINT:
		WM_GetClientRect(&r);
		//GUI_SetColor(0x000000);
		//GUI_DrawRect(r.x0, r.y0, r.x1, r.y1);          /* Draw rectangle around it */
		///* Draw the bright sides */
		//GUI_SetColor(0xffffff);
		//GUI_DrawHLine(r.y0 + 1, r.x0 + 1, r.x1 - 2);   /* Draw top line */
		//GUI_DrawVLine(r.x0 + 1, r.y0 + 1, r.y1 - 2);
		///* Draw the dark sides */
		//GUI_SetColor(0x555555);
		//GUI_DrawHLine(r.y1-1, r.x0 + 1, r.x1 - 1);
		//GUI_DrawVLine(r.x1-1, r.y0 + 1, r.y1 - 2);
		break;
	case WM_INIT_DIALOG:
		for (i = 0; i < GUI_COUNTOF(_aDialogNumPad) - 1; i++) {
			hItem = WM_GetDialogItem(hDlg, GUI_ID_USER + i+50);
			BUTTON_SetFocussable(hItem, 0);                       /* Set all buttons non focussable */
			switch (i) {
			case 13:
				BUTTON_SetBitmapEx(hItem, 0, &_bmArrowLeft, 7, 7);  /* Set bitmap for arrow left button (unpressed) */
				BUTTON_SetBitmapEx(hItem, 1, &_bmArrowLeft, 7, 7);  /* Set bitmap for arrow left button (pressed) */
				break;
			case 14:
				BUTTON_SetBitmapEx(hItem, 0, &_bmArrowRight, 7, 7); /* Set bitmap for arrow right button (unpressed) */
				BUTTON_SetBitmapEx(hItem, 1, &_bmArrowRight, 7, 7); /* Set bitmap for arrow right button (pressed) */
				break;
			}
		}
		WM_GetDialogItem(hDlg, GUI_ID_USER + 12+50);
		break;
	case WM_NOTIFY_PARENT:
		Id    = WM_GetId(pMsg->hWinSrc);      /* Id of widget */
		NCode = pMsg->Data.v;                 /* Notification code */
		switch (NCode) {
		case WM_NOTIFICATION_CLICKED:
			Pressed = 1;
		case WM_NOTIFICATION_RELEASED:
			if ((Id >= GUI_ID_USER+50) && (Id <= (GUI_ID_USER + GUI_COUNTOF(_aDialogNumPad) - 1+50))) {
				int Key;
				if (Id < GUI_ID_USER + 11+50) {
					char acBuffer[10];
					BUTTON_GetText(pMsg->hWinSrc, acBuffer, sizeof(acBuffer)); /* Get the text of the button */
					Key = acBuffer[0];
				} else {
					Key = _aKey[Id - GUI_ID_USER - 11-50];                        /* Get the text from the array */
				}
				GUI_SendKeyMsg(Key, Pressed);                                /* Send a key message to the focussed window */
			}
			break;
		}
	default:
		WM_DefaultProc(pMsg);
	}
}
// USER START (Optionally insert additional static code)

 
#endif 
