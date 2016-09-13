#include "TXLib.h"

struct C_Ball
    {
    double x, y;
    double vx, vy;
    double r;
    COLORREF color;
    };

double VX [50] = {}, VY [50] = {};
int N_M = 0;
double k = 1;

void Mass_Ball (C_Ball b [], int N);
void Dvig_and_draw (C_Ball b [], int N);
double Dist (double x1, double y1, double x2, double y2);
double F_k(double D, double m1, double m2);
void Osnovn ();

double XWindow = GetSystemMetrics (SM_CXSCREEN), YWindow = GetSystemMetrics (SM_CYSCREEN);

int main ()
    {
    _txWindowStyle &= ~ WS_CAPTION;
    txCreateWindow (XWindow, YWindow);
    txTextCursor (false);
    Osnovn ();
    }

void Osnovn ()
    {
    C_Ball ball [10] = {};
    Mass_Ball (ball, 10);
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
        Dvig_and_draw (ball, 10);
        if (GetAsyncKeyState (VK_UP) && k != 0.025) k -= 0.025;
        if (GetAsyncKeyState (VK_DOWN)) k += 0.025;
        printf ("%g,\n\n\n\n\n\n\n\n\n\n\n\n\n ", k);
        txSleep (10);
        txEnd ();
        }
    }

void Mass_Ball (C_Ball b [], int N)
    {
    for (int i = 0; i < N; i++)
        {
        b[i].r  = 20;
        b[i].x  = random (b[i].r, XWindow - b[i].r);
        b[i].y  = random (b[i].r, YWindow - b[i].r);
        b[i].vx = 10;
        b[i].vy = 10;
        b[i].color = RGB (0, 255, 0);
        }
    }

void Dvig_and_draw (C_Ball b [], int N)
    {
    double d = 0, d_c = 0;
    double V_ob = 0;
    double F_k_x = 0, F_k_y = 0;
    double X = txMouseX (), Y = txMouseY ();

    txSetColor     (RGB (255, 0, 0));
    txSetFillColor (RGB (255, 0, 0));
    txCircle (X, Y, 30);

    for (int i = 0; i < N; i++, N_M ++)
        {
        /*N_M = N_M%50;*/
        d = Dist (X, Y, b[i].x, b[i].y);
        if (d > 765) d_c = 255;
        else         d_c = d / 3;
        b[i].color = RGB (d_c, d_c, 255 - d_c);

        F_k_x = F_k (X - b[i].x, b[i].r, 2000);
        F_k_y = F_k (Y - b[i].y, b[i].r, 2000);
        printf ("%g, %g, ", F_k_x, F_k_y);

        b[i].vx = -fabs (X - b[i].x) / (X - b[i].x) + F_k_x / b[i].r * fabs (X - b[i].x) / (X - b[i].x);
        b[i].vy = -fabs (Y - b[i].y) / (Y - b[i].y) + F_k_y / b[i].r * fabs (Y - b[i].y) / (Y - b[i].y);

        printf ("%g, %g, \n", b[i].vx, b[i].vy);
      /*VX[N_M] = (txMouseX() - b[i].x) / k(txMouseX() - b[i].x);
        VY[N_M] = (txMouseY() - b[i].y) / k;

        if (fabs(txMouseX() - b[i].x) <= 5 * b[i].r &&
            fabs(txMouseY() - b[i].y) <= 5 * b[i].r)
            {
            VX[N_M] = -VX[N_M] * 1500;
            VY[N_M] = -VY[N_M] * 1500;
            }*/

        b[i].x += b[i].vx;
        b[i].y += b[i].vy;

        /*V_ob = Dist (0, 0, b[i].vx, b[i].vy);
        if (V_ob > 255) V_ob = 255;

        b[i].color = RGB (V_ob, 255 - V_ob, 0); */
        txSetColor     (b[i].color);
        txSetFillColor (b[i].color);
        txCircle (b[i].x, b[i].y, b[i].r);
        }
    }

double F_k(double D, double m1, double m2)
    {
    return k * m1 * m2 / D;
    }

double Dist (double x1, double y1, double x2, double y2)
    {
    return sqrt ((x2- x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    }
