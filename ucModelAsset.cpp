//---------------------------------------------------------------------------

#include "ucModelAsset.h"
#include <string>

//---------------------------------------------------------------------------
#pragma package(smart_init)

// returns the candle list associated with the time from
CandleList* AssetCandles::candleListByInterval( const int &pinterval ) {

    if ( pinterval == 5000 ) {

        return candlelist5s ;

    } else {

        return candlelist1m ;

    }

}

// resets cursor
void AssetCandles::resetCursor() {

    cursor = 0 ;

}


// this method is used to add candle items (as pointers) from Assets to Main (Total)
void AssetCandles::AppendFromCursorTo( CandleList* &pcandlelist, TimeStamp &puntilts ) {


   CandleList* candelist = candleListByInterval( pcandlelist->getintervalMS() ) ;

   while ( cursor < candelist->Count() &&
           dynamic_cast<Candle*> ( candelist->GetItem( cursor ) )->gettsclose().getText() <= puntilts.getText() ) {

       pcandlelist->Add( candelist->GetItem( cursor ) ) ;

       cursor ++ ;
   }


}

// Create and/or manage 5s candle item values from ticker
void AssetCandles::ComputeTicker( Ticker* pticker ) {

  candlelist5s->ComputeTicker( pticker ) ;

}

// creates 2 candle list (5s and 1min)
AssetCandles::AssetCandles( IT* powner ):Asset( powner ) {

 candlelist5s = new CandleList( this, 5000 ) ;
 candlelist1m = new CandleList( this, 60000 ) ;

}

// destroys 2 candle list (5s and 1min)
AssetCandles::~AssetCandles() {

    delete ( candlelist5s ) ;
    delete ( candlelist1m ) ;

}

// getter from 5s candle list
const CandleList* AssetCandles::getCandleList5s() const {

    return candlelist5s ;

}

// getter from 1min candle list
const CandleList* AssetCandles::getCandleList1m() const {

    return candlelist1m ;

}

// Create 1min candles from 5s candles
void AssetCandles::Create1mCandles() {

    // full loop
    for (int i = 0; i < candlelist5s->Count(); i++) {

        // retrieve 5s candle item
        Candle* candle5s = dynamic_cast<Candle*>( candlelist5s->GetItem( i ) ) ;

        // create and/or manage 1min candle item
        Candle* candle1m = candlelist1m->candlefromTimeStamp( candle5s->getsymbol(),
                                                               candle5s->gettsopen() ) ;

        const string ptickerlastprice = "tkr_lastprice" ;
        const string ptickervolume    = "tkr_volume"    ;

        // Feed 1min candles in the form of tickers (extracted from 5s candles)
        candle1m->ComputeTicker( ptickerlastprice, candle5s->getopen() ) ;
        candle1m->ComputeTicker( ptickerlastprice, candle5s->gethigh() ) ;
        candle1m->ComputeTicker( ptickerlastprice, candle5s->getlow() ) ;
        candle1m->ComputeTicker( ptickerlastprice, candle5s->getclose() ) ;
        candle1m->ComputeTicker( ptickervolume,    candle5s->getvolume() ) ;

    }

}

// Reset all Cursors (for each asset)
void AssetCandlesList::resetCursors() {

   for ( int i = 0; i < Count(); i++ ) {

       AssetCandles* assetcandles = dynamic_cast<AssetCandles*>( GetItem( i ) ) ;

       assetcandles->resetCursor() ;

   }

}

// Feed main candles list (5s and 1min) from assets candle list
// Candles are inserted as pointers
void AssetCandlesList::FeedMainCandlesCandleList( CandleList* pcandlelist ) {

    TimeStamp untilts ;

    // these candles lists begin at 09:30.
    untilts.setText( "01/08/2023 09:30:05.000" ) ;

    // Define timestamp
    TimeStamp itv { 0, 0, 0, 0, 0, 5, 0 } ;

    resetCursors() ;

    // loop until 16:00
    while ( untilts.getText() <= "01/08/2023 16:00:00.000" ) {


        // loop for each asset
        for ( int i = 0; i < Count(); i++) {

         AssetCandles* assetcandles = dynamic_cast<AssetCandles*>( GetItem( i ) ) ;

         // this cursor control is necessary because some assets have gaps in between the candles
         // sometimes there is no trades on a specific interval of a given time stamp
         assetcandles->AppendFromCursorTo( pcandlelist, untilts ) ;

        }

        // increments the cursor
        untilts += itv ;

    }

};

// create main candle lists (5s and 1min)
AssetCandlesList::AssetCandlesList( IT* powner ):AssetList( powner ) {

    maincandlelist5s = new CandleList( this, 5000  ) ;
    maincandlelist1m = new CandleList( this, 60000 ) ;


} ;

// destroy main candle lists (5s and 1min)
AssetCandlesList::~AssetCandlesList( ) {

    delete maincandlelist1m ;
    delete maincandlelist5s ;

} ;

// getter for 5 seconds candle list (main candle list)
CandleList* AssetCandlesList::getmaincandlelist5s() {

    return maincandlelist5s ;

}

// getter for 1 minute candle list (main candle list)
CandleList* AssetCandlesList::getmaincandlelist1m() {

    return maincandlelist1m ;

}

// Feed main candles using pointers to asset candles
void AssetCandlesList::FeedMainCandles() {

    FeedMainCandlesCandleList( maincandlelist5s ) ;
    FeedMainCandlesCandleList( maincandlelist1m ) ;

}

// create Asset class and return as IT* pointer
IT* AssetList::getnewIT() {

    IT* aThis = this ;

    return new Asset(aThis ) ;

} ;

// create AssetCandles class and return as IT* pointer
IT* AssetCandlesList::getnewIT() {

    IT* aThis = this ;

    return new AssetCandles(aThis ) ;

} ;