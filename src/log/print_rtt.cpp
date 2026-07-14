#include "SEGGER_RTT.h"

extern "C" void etl_putchar(int c)
{
    SEGGER_RTT_PutCharSkipNoLock(0, static_cast<char>(c));
}
