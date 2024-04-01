//---------------------------------------------------------------------------

#include <cmath>
#include "ucModelCandles.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

// initializes the candle
void Candle::InitStatic() {

    tsopen.Init()  ;
    tsclose.Init() ;
    symbol = ""    ;
    open   = 0     ;
    close  = 0     ;
    high   = 0     ;
    low    = 0     ;
    volume = 0     ;

}

Candle::Candle( IT* powner ):IT( powner ) {

    InitStatic() ;

} ;

// calls InitStatic
void Candle::Init() {

    IT::Init() ;

    InitStatic() ;

}

// fill candle attributes from ticker
void Candle::ComputeTicker( const string &pticker,
                            const double &value ) {

    // fills OCHL info everytime pticker represents last price
    if ( pticker == "tkr_lastprice" ) {

        if ( open == 0 ) {

            open = value ;

        }

        close = value ;

        if ( low == 0 || value < low ) {


            low = value ;

        }

        if ( value > high ) {


            high = value ;

        }

    } else

    // adds volume info
    if ( pticker == "tkr_volume" ) {

        setvolume( getvolume() + trunc( value ) ) ;

    }

}

IT* CandleList::getnewIT() {

 return new Candle( this ) ;

}

// define time frame
CandleList::CandleList( IT* powner, int pintervalMS ):ITList( powner ) {

 vintervalMS = pintervalMS ;

}  ;

// getter
int CandleList::getintervalMS() const {

    return vintervalMS ;

}

// create or return previously created candle for a given timestamp
Candle* CandleList::candlefromTimeStamp( const string &psymbol, const TimeStamp &pts ) {

    TimeStamp tsfrom = pts.roundTimeStamp( vintervalMS ) ;

    Candle* lastcandle = dynamic_cast<Candle*>( Last() ) ;

    const bool first = lastcandle == nullptr ;

    if ( first || lastcandle->gettsopen().getText() != tsfrom.getText() ) {

        lastcandle = dynamic_cast<Candle*>( Add() ) ;
        lastcandle->settsopen ( tsfrom ) ;
        lastcandle->settsclose( tsfrom.AddMs( vintervalMS ) ) ;
        lastcandle->setsymbol( psymbol ) ;

    }

    return lastcandle ;

}

// create correspondent candle from ticker and fills its attributes
void CandleList::ComputeTicker( const Ticker* pticker ) {

    Candle* lastcandle = candlefromTimeStamp( pticker->getsymbol(),
                                              pticker->getts() ) ;

    lastcandle->ComputeTicker( pticker->getticker(),
                               pticker->getvalue() ) ;

}
