//---------------------------------------------------------------------------

#ifndef ucModelAssetH
#define ucModelAssetH
//---------------------------------------------------------------------------

#include "Base/ucModelCad.h"
#include "ucModelCandles.h"
#include "Generic/uAux.h"


#endif


 /* TODO -oEmerson -cBug Fix : Binary Search Control */

class Asset : public ITId {
private:

public:

    Asset( IT* powner = nullptr ):ITId( powner ) {} ;

};

class AssetList : public ITIdList {
protected :

  // create Asset class and return as IT* pointer
  IT* getnewIT() override ;

public :

   AssetList( IT* powner = nullptr ):ITIdList( powner ) {} ;

} ;


// class to hold 5s and 1min candle list
class AssetCandles : public Asset {
private:

    // variable to hold 5s candles
    CandleList* candlelist5s ;

    // variable to hold 1min candles
    CandleList* candlelist1m ;

    // cursor is used to hold current position of the candle item
    int cursor ;

    // returns the candle list based on time frame
    CandleList* candleListByInterval( const int &pinterval ) ;

public:

    AssetCandles( IT* powner = nullptr ) ;

    ~AssetCandles() ;

    // resets cursor
    void resetCursor() ;

    // creates candle lines from cursor to given TimeStamp
    void AppendFromCursorTo( CandleList* &pcandlelist, TimeStamp &puntilts ) ;

    // Create and/or manage 5s candle item values from ticker
    void ComputeTicker( Ticker* pticker ) ;

    // getter from 5s candle list
    const CandleList* getCandleList5s() const ;

    // getter from 1min candle list
    const CandleList* getCandleList1m() const ;

    // Create 1min candles from 5s candles
    void Create1mCandles() ;

} ;

// class to hold candles for each asset
// (inherited from AssetList)
class AssetCandlesList : public AssetList {
private:

    // variable to hold main 5s candle list
    CandleList* maincandlelist5s ;

    // variable to hold main 1min candle list
    CandleList* maincandlelist1m ;

    // Reset all Cursors (for each asset)
    void resetCursors() ;

    // Feed main candles list (5s and 1min) from assets candle list
    // Candles are inserted as pointers
    void FeedMainCandlesCandleList( CandleList* pcandlelist ) ;

protected :

    // create AssetCandles class and return as IT* pointer
    IT* getnewIT() override ;

public :

    AssetCandlesList( IT* powner = nullptr ) ;

    ~AssetCandlesList( ) ;

    // getter for 1 minute candle list (main candle list)
    CandleList* getmaincandlelist1m() ;

    // getter for 5 seconds candle list (main candle list)
    CandleList* getmaincandlelist5s() ;

    // Feed main candles using pointers to asset candles
    void FeedMainCandles() ;

} ;

