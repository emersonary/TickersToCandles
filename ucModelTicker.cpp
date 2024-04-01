//---------------------------------------------------------------------------

#include <cmath>
#include "ucModelTicker.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

// Assign one time stamp to another
void TimeStamp::Assign( const TimeStamp &pts ) {

    year   = pts.year   ;
    month  = pts.month  ;
    day    = pts.day    ;
    hour   = pts.hour   ;
    minute = pts.minute ;
    sec    = pts.sec    ;
    ms     = pts.ms     ;

}

// fixes negative or overflowed values after sum and substraction operations
void TimeStamp::fixoutbounds( TimeStamp &ts ) const {


    while ( ts.ms > 999 ) {

     ts.sec++ ;

     ts.ms -= 1000 ;

    }

    while ( ts.ms < 0 ) {

     ts.sec-- ;

     ts.ms += 1000 ;

    }

    while ( ts.sec > 59 ) {

     ts.minute++ ;

     ts.sec -= 60 ;

    }

    while ( ts.sec < 0 ) {

     ts.minute-- ;

     ts.sec += 60 ;

    }

    while ( ts.minute > 59 ) {

     ts.hour++ ;

     ts.minute -= 60 ;

    }

    while ( ts.minute < 0 ) {

     ts.hour-- ;

     ts.minute += 60 ;

    }

    while ( ts.hour > 23 ) {

     ts.day++ ;

     ts.hour -= 24 ;

    }

    while ( ts.hour < 0 ) {

     ts.day-- ;

     ts.hour += 24 ;

    }


}

// method called by operators to sum or substract values
void TimeStamp::SumOp( TimeStamp &result, TimeStamp &ts, const int &oper ) {

         result.year   = year   + ( ts.year   * oper ) ;
         result.month  = month  + ( ts.month  * oper ) ;
         result.day    = day    + ( ts.day    * oper ) ;
         result.hour   = hour   + ( ts.hour   * oper ) ;
         result.minute = minute + ( ts.minute * oper ) ;
         result.sec    = sec    + ( ts.sec    * oper ) ;
         result.ms     = ms     + ( ts.ms     * oper ) ;

         fixoutbounds( result ) ;
}

int year   ; // 0-based
int month  ; // [1-12]
int day    ; // [1-31]
int hour   ; // [0-23]
int minute ; // [0-59]
int sec    ; // [0-59]
int ms     ; // [0-999]

void Init() {

    year   = 0 ;
    month  = 0 ;
    day    = 0 ;
    hour   = 0 ;
    minute = 0 ;
    sec    = 0 ;
    ms     = 0 ;

}

// convert to string
string TimeStamp::getText() const {

    return padTo( to_string( day ), 2, '0' )    + "/" +
           padTo( to_string( month ), 2, '0' )  + "/" +
           padTo( to_string( year ), 4, '0' )   + " " +
           padTo( to_string( hour ), 2, '0' )   + ":" +
           padTo( to_string( minute ), 2, '0' ) + ":" +
           padTo( to_string( sec ), 2, '0' )    + ( ms != 0 ? "." + padTo( to_string( ms ), 3, '0' ) : "" ) ;

}

// set attributes from string
void TimeStamp::setText( const string &txt ) {

   day    = stoi( txt.substr( 0, 2 ) ) ;
   month  = stoi( txt.substr( 3, 2 ) ) ;
   year   = stoi( txt.substr( 6, 4 ) ) ;
   hour   = stoi( txt.substr( 11, 2 ) ) ;
   minute = stoi( txt.substr( 14, 2 ) ) ;
   sec    = stoi( txt.substr( 17, 2 ) ) ;
   ms     = stoi( txt.substr( 20, 3 ) ) ;

}

// returns rounded TimeStamp according to time frame
TimeStamp TimeStamp::roundTimeStamp( const int &pintervalms ) const {

    TimeStamp result ;

    result.Assign( *this ) ;

    unsigned int lint = result.sec * 1000 + result.ms ;

    unsigned int lfrom = ( lint / pintervalms ) * pintervalms / 1000 ;

    result.ms = 0 ;

    result.sec = lfrom ;

    return result ;

}

// Adds milliseconds to TimeStamp (verify if it can be replaced with + operator)
TimeStamp TimeStamp::AddMs( const int &pintervalms ) const {

    TimeStamp result ;

    result.Assign( *this ) ;

    result.sec = result.sec + trunc( pintervalms / 1000 ) ;

    if (result.sec >= 60 ) {

        result.sec = 0 ;
        result.minute++ ;

        if ( result.minute >= 60 ) {

            result.minute = 0 ;
            result.hour++ ;

        }

        return result ;


    }

    return result ;

}

// Initialize TimeStamp
void TimeStamp::Init() {

    year   = 0 ;
    month  = 0 ;
    day    = 0 ;
    hour   = 0 ;
    minute = 0 ;
    sec    = 0 ;
    ms     = 0 ;

}

// returns time stamp as string
string Ticker::gettstxt() {

    return ts.getText() ;

}

// sets time stamp from string
void Ticker::settstext( const string &ptstxt ) {

    ts.setText( ptstxt ) ;

}

// creates Ticker class and returns it at "IT"
IT* TickerList::getnewIT() {

    return new Ticker( this ) ;

} ;

// get local time
TimeStamp get_local_date()
{
    TimeStamp t{};

    auto now = std::chrono::system_clock::now();
    auto seconds = std::chrono::time_point_cast<std::chrono::seconds>(now);
    auto fraction = now - seconds;
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(fraction);

    time_t tnow = std::chrono::system_clock::to_time_t(now);
    tm* ptm = localtime(&tnow);

    t.year = ptm->tm_year + 1990;
    t.month = ptm->tm_mon + 1;
    t.day = ptm->tm_mday;
    t.hour = ptm->tm_hour;
    t.minute = ptm->tm_min;
    t.sec = ptm->tm_sec;
    t.ms = static_cast<int>(milliseconds.count());

    return t;
}
