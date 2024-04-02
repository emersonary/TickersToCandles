//---------------------------------------------------------------------------

#pragma once

#ifndef ucModelCandlesH
#define ucModelCandlesH

#include <string>
#include <fstream>
#include <iostream>

#include "ucModelCad.h"
#include <uAux.h>
#include "ucModelTicker.h"

using namespace std ;

//---------------------------------------------------------------------------
#endif

// class to represent a candle
// OCHL and volume attributes.
class Candle : public IT {
private:

    string    symbol  ; // symbol
    TimeStamp tsopen  ; // open time stamp
    TimeStamp tsclose ; // close time stamp
    double    open    ; // open value
    double    close   ; // close value
    double    high    ; // high value
    double    low     ; // low value
    int       volume  ; // volume value

    // initializes the candle
    void InitStatic() ;

public:

    Candle( IT* powner ) ;

    // getters
    string    getsymbol  () const { return symbol  ; } ;
    TimeStamp gettsopen  () const { return tsopen  ; } ;
    TimeStamp gettsclose () const { return tsclose ; } ;
    double    getopen    () const { return open    ; } ;
    double    getclose   () const { return close   ; } ;
    double    gethigh    () const { return high    ; } ;
    double    getlow     () const { return low     ; } ;
    int       getvolume  () const { return volume  ; } ;

    // setters
    void setsymbol  ( const string    &psymbol  ) { symbol  = psymbol  ; } ;
    void settsopen  ( const TimeStamp &ptsopen  ) { tsopen  = ptsopen  ; } ;
    void settsclose ( const TimeStamp &ptsclose ) { tsclose = ptsclose ; } ;
    void setopen    ( const double    &popen    ) { open    = popen    ; } ;
    void setclose   ( const double    &pclose   ) { close   = pclose   ; } ;
    void sethigh    ( const double    &phigh    ) { high    = phigh    ; } ;
    void setlow     ( const double    &plow     ) { low     = plow     ; } ;
    void setvolume  ( const int       &pvolume  ) { volume  = pvolume  ; } ;

    void Init() override ;

    // fill candle attributes from ticker
    void ComputeTicker( const string &pticker,
                        const double &value ) ;
};

// class to represent candle list
class CandleList : public ITList {
protected :

  IT* getnewIT() override ;

  // vairable to hold time frame of candles.
  int vintervalMS ;

public :

   // define time frame
   CandleList( IT* powner = nullptr, int pintervalMS = 0 ) ;

   // getter
   int getintervalMS() const ;

   // create or return previously created candle for a given timestamp
   Candle* candlefromTimeStamp( const string &psymbol, const TimeStamp &pts ) ;

   // create correspondent candle from ticker and fills its attributes
   void ComputeTicker( const Ticker* pticker ) ;

} ;



