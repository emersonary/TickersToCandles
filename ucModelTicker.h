//---------------------------------------------------------------------------

#pragma once

#ifndef ucModelTickerH
#define ucModelTickerH

#include <string>
#include <chrono>
#include <ctime>

#include "ucModelBase.h"
#include "uAux.h"

//---------------------------------------------------------------------------
#endif

using namespace std ;

// struct to represent TimeStamp
// this was created to support specific candle list creation
struct TimeStamp
{
private :

    // Assign one time stamp to another
    // (replace it with = operator)
    void Assign( const TimeStamp &pts ) ;

    // fixes negative or overflowed values after sum and substraction operations
    void fixoutbounds( TimeStamp &ts ) const ;

    // method called by operators to sum or substract values
    // third parameter can be 1 or -1
    void SumOp( TimeStamp &result, TimeStamp &ts, const int &oper = 1 ) ;

public :

    // operator to compare 2 timestamps
    bool operator != ( TimeStamp& a ) {

        return
            ( a.year   != year   ) ||
            ( a.month  != month  ) ||
            ( a.day    != day    ) ||
            ( a.hour   != hour   ) ||
            ( a.minute != minute ) ||
            ( a.sec    != sec    ) ||
            ( a.ms     != ms     ) ;


    }

    // operator to sum 2 timestamps
    TimeStamp operator + ( TimeStamp& a ) {

             TimeStamp result ;

             SumOp( result, a ) ;

             return result ;

    }

    // operator to sum 1 timestamp to itself

    TimeStamp operator += ( TimeStamp& a ) {

             year   = year   + a.year   ;
             month  = month  + a.month  ;
             day    = day    + a.day    ;
             hour   = hour   + a.hour   ;
             minute = minute + a.minute ;
             sec    = sec    + a.sec    ;
             ms     = ms     + a.ms     ;

             fixoutbounds( *this ) ;

             return *this ;

    }

    // operator to substract 2 timestamps
    TimeStamp operator - ( TimeStamp& a ) {

       TimeStamp result ;

       SumOp( result, a, -1 ) ;

       fixoutbounds( result ) ;

       return result ;

    }

    // Attributes
    int year   ; // 0-based
    int month  ; // [1-12]
    int day    ; // [1-31]
    int hour   ; // [0-23]
    int minute ; // [0-59]
    int sec    ; // [0-59]
    int ms     ; // [0-999]

    // Initialize TimeStamp
    void Init() ;

    // convert to string
    string getText() const ;

    // set attributes from string
    void setText( const string &txt ) ;

    // returns rounded TimeStamp according to time frame
    TimeStamp roundTimeStamp( const int &pintervalms ) const ;

    // Adds milliseconds to TimeStamp (verify if it can be replaced with + operator)
    TimeStamp AddMs( const int &pintervalms ) const ;

};

TimeStamp get_local_date() ;

// class to represent to Ticker
class Ticker : public IT {
private:

    TimeStamp ts     ; // time stamp
    string    symbol ; // symbol (asset)
    string    ticker ; // ticket time (last price or volume)
    double    value  ; // value

public:

    Ticker( IT* powner ):IT( powner ) {} ;

    // getters
    TimeStamp getts     () const { return ts     ; }
    string    getsymbol () const { return symbol ; }
    string    getticker () const { return ticker ; }
    double    getvalue  () const { return value  ; }

    // setters
    void setts     ( const TimeStamp &pts   ) { ts     = pts     ; }
    void setsymbol ( const string &psymbol  ) { symbol = psymbol ; }
    void setticker ( const string &pticker  ) { ticker = pticker ; }
    void setvalue  ( const double &pvalue   ) { value  = pvalue  ; }

    // returns time stamp as string
    string gettstxt() ;

    // sets time stamp from string
    void settstext( const string &ptstxt ) ;

};

// class to represent ticket list
class TickerList : public ITList {
protected:

    // creates Ticker class and returns it at "IT"
    IT* getnewIT() override ;

public:

   TickerList( IT* powner = nullptr ):ITList( powner )  {}

} ;


