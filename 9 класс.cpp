#include "TXLib.h"

struct C_Ball
    {
    double x, y;
    double vx, vy;
    double r;
    COLORREF color;
    double Red;
    };

void Mass_Ball (C_Ball b [], int N);
void Dvig_and_draw (C_Ball b [], int N);
double Dist (double x1, double y1, double x2, double y2);
void Ottalkiv (int n, C_Ball b[]);

double XWindow = GetSystemMetrics (SM_CXSCREEN), YWindow = GetSystemMetrics (SM_CYSCREEN);

int main ()
    {
    _txWindowStyle &= ~ WS_CAPTION;
    txCreateWindow (XWindow, YWindow);
    C_Ball ball [4500] = {};
    Mass_Ball (ball, 4500);
    for (int i = 0;; i++)
        {
        txBegin ();
        if (!GetAsyncKeyState (VK_SPACE))
            {
            txSetFillColor (TX_BLACK);
            txSetColor (TX_BLACK);
            txClear ();
            }
        Dvig_and_draw (ball, 4500);
        txSleep (0);
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
        b[i].color = RGB (255, 0, 0);
        }
    }

void Dvig_and_draw (C_Ball b [], int N)
    {
    for (int i = 0; i < N; i++)
        {
        b[i].x += b[i].vx;
        b[i].y += b[i].vy;
        }

    for (int i = 0; i < N; i++)
        {
        if (b[i].x + b[i].r >= XWindow)
            {
            b[i].vx = -b[i].vx;
            b[i].x = XWindow - b[i].r;
            b[i].Red = 255;
            }
        if (b[i].x - b[i].r <= 0)
            {
            b[i].vx = -b[i].vx;
            b[i].x = b[i].r;
            b[i].Red = 255;
            }

        if (b[i].y + b[i].r >= YWindow)
            {
            b[i].vy = -b[i].vy;
            b[i].y = YWindow - b[i].r;
            b[i].Red = 255;
            }
        if (b[i].y - b[i].r <= 0)
            {
            b[i].vy = -b[i].vy;
            b[i].y = b[i].r;
            b[i].Red = 255;
            }

        if (b[i].Red - Dist (0, 0, b[i].vx, b[i].vy) / 3 > 0) b[i].Red -= Dist (0, 0, b[i].vx, b[i].vy) / 3;
        b[i].color = RGB (b[i].Red, 0, 255 - b[i].Red);

        txSetColor (b[i].color);
        txSetFillColor (b[i].color);
        txCircle (b[i].x, b[i].y, b[i].r);
        }

    Ottalkiv (N, b);
    }

double Dist (double x1, double y1, double x2, double y2)
    {
    return sqrt ((x2- x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    }

void Ottalkiv (int n, C_Ball b[])
    {
    for (int i = 0; i < n; i++)
        {
        for (int k = 1; k < n && k > i; k++)
            {
            if (fabs (b[i].x - b[k].x) <= b[i].r + b[k].r + 2 && fabs (b[i].y - b[k].y) <= b [i].r + b [k].r + 2 && k != n)
                {
                if (Dist (b[k].x, b[k].y, b[i].x, b[i].y) <= b [i].r + b [k].r + 2)
                    {
                    double vx = b[i].vx, vy = b[i].vy;
                    b[i].vx = b[k].r * b[k].r / b[i].r / b[i].r * b[k].vx;
                    b[i].vy = b[k].r * b[k].r / b[i].r / b[i].r * b[k].vy;
                    b[k].vx = b[i].r * b[i].r / b[k].r / b[k].r * vx;
                    b[k].vy = b[i].r * b[i].r / b[k].r / b[k].r * vy;
                    b[i].Red = 255;
                    b[k].Red = 255;
                    }
                }
            }
        }
    }
