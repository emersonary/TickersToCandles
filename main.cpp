#include <iostream>
#include "ucCtrlTickersToCandles.h"

int main() {

    TickerToCandleCtrl tickerToCandle ;

    tickerToCandle.ExecTickersToCandles() ;

    std::cout << "Files created!" << std::endl;
    return 0;
}
