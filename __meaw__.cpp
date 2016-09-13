#include "TXLib.h"

struct C_Ball
    {
    double x, y;
    double vx, vy;
    double r;
    COLORREF color;
    };

double XWindow = GetSystemMetrics (SM_CXSCREEN), YWindow = GetSystemMetrics (SM_CYSCREEN);

void Mass_Ball (C_Ball b [], int N);
void Osnov ();
void Dvig_and_draw (C_Ball b [], int N);
double Dist (double x1, double y1, double x2, double y2);

int main ()
    {
    _txWindowStyle &= ~ WS_CAPTION;
    txCreateWindow (XWindow, YWindow);
    txTextCursor (false);
    Osnov ();
    }

void Osnov ()
    {
    C_Ball ball [30] = {};
    Mass_Ball (ball, 30);
    printf ("\n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n ");
    for (int i = 0; !GetAsyncKeyState (VK_ESCAPE); i++)
        {
        txBegin ();
        if (!GetAsyncKeyState (VK_SPACE))
            {
            txSetFillColor (TX_BLACK);
            txSetColor (TX_BLACK);
            txClear ();
            }
        Dvig_and_draw (ball, 30);
        txSleep (10);
        txEnd ();
        }
    }

void Mass_Ball (C_Ball b [], int N)
    {
    for (int i = 0; i < N; i++)
        {
        b[i].r  = random (5, 20);
        b[i].x  = random (b[i].r, XWindow - b[i].r);
        b[i].y  = random (b[i].r, YWindow - b[i].r);
        b[i].vx = random (-5, 5);
        b[i].vy = random (-5, 5);
        b[i].color = RGB (random (155, 255), random (155, 255), random (155, 255));
        }
    }

void Dvig_and_draw (C_Ball b [], int N)
    {
    for (int i = 0; i < N; i++)
        {
        if (b[i].x + b[i].r >= XWindow)
            {
            b[i].vx = -b[i].vx;
            b[i].x = XWindow - b[i].r;
            }
        if (b[i].x - b[i].r <= 0)
            {
            b[i].vx = -b[i].vx;
            b[i].x = b[i].r;
            }

        if (b[i].y + b[i].r >= YWindow)
            {
            b[i].vy = -b[i].vy + 5;
            b[i].y = YWindow - b[i].r;
            }
        if (b[i].y - b[i].r <= 0)
            {
            b[i].vy = -b[i].vy;
            b[i].y = b[i].r;
            }
        b[i].vy ++;

        b[i].x += b[i].vx;
        b[i].y += b[i].vy;
        txSetColor     (b[i].color);
        txSetFillColor (b[i].color);
        txCircle (b[i].x, b[i].y, b[i].r);
        }
    }

double Dist (double x1, double y1, double x2, double y2)
    {
    return sqrt ((x2- x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    }
