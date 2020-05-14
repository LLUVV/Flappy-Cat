#include "kb_input2.h"
#include<time.h>
HANDLE Stdin;
INPUT_RECORD ir;
DWORD Read = 0;

void	initializeKeyInput(void)
{
   if ((Stdin = GetStdHandle (STD_INPUT_HANDLE)) == NULL)
      exit(1);
   SetConsoleMode (Stdin, ENABLE_LINE_INPUT);
}

int waitForKeyDown(float sec)
{
   if (WAIT_TIMEOUT == WaitForSingleObject (Stdin, (int)(sec*1000) ))
      return 0;
   else
      return 1;
}

int getKeyEventASCII(void)
{
   ReadConsoleInput(Stdin, &ir, 1, &Read);
   FlushConsoleInputBuffer(Stdin);
   if (ir.EventType == KEY_EVENT && ir.Event.KeyEvent.bKeyDown)
      return ir.Event.KeyEvent.uChar.AsciiChar;
   else
      return -1;
}

int getKeyEventVirtual(void)
{
   ReadConsoleInput(Stdin, &ir, 1, &Read);
   FlushConsoleInputBuffer(Stdin);
   if (ir.EventType == KEY_EVENT && ir.Event.KeyEvent.bKeyDown)
      return ir.Event.KeyEvent.wVirtualKeyCode;
   else
      return -1;
}
int getKeyEventVirtual_timelimit(void)
{
    time_t count=0;
    while(1)
    {
        if(ReadConsoleInput(Stdin, &ir, 1, &Read))break;
        count=clock();
        if(count/CLOCKS_PER_SEC>3) return;
    }
    FlushConsoleInputBuffer(Stdin);
    if (ir.EventType == KEY_EVENT && ir.Event.KeyEvent.bKeyDown)
        return ir.Event.KeyEvent.wVirtualKeyCode;
    else
        return -1;
}

