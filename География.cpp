#include "TXLib.h"

double XWindow = GetSystemMetrics (SM_CXSCREEN), YWindow = GetSystemMetrics (SM_CYSCREEN);

int main ()
    {
    _txWindowStyle &= ~ WS_CAPTION;
    txCreateWindow (XWindow, YWindow);
    }

void menu ()
    {

    }
