#include <iostream>
#include "ucCtrlTickersToCandles.h"

int main() {

    TickerToCandleCtrl tickerToCandle ;

    tickerToCandle.ExecTickersToCandles() ;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
