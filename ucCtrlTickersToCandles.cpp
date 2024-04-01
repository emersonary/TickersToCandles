//---------------------------------------------------------------------------

#include <cmath>
#include <string>

#include "ucCtrlTickersToCandles.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

// method to read tickers and mounts candles into memory
void TickerToCandleCtrl::ExecTickersToCandles() {

    string str ;

    int first = true ;

    // define filename and folder
    string filename = "C:\\draft\\tickers.csv" ;

    string folder = putBarra( getPathName( filename ) ) ;

    string outputfolder = folder + "\\output\\" ;

    // open filename (CSV)
    ifstream textfile( filename ) ;

    // iterate csv file to get all its lines
    while ( getline( textfile, str ) ) {

        // ignore the first line (column titles)
        if ( first ) {

         first = false ;

         continue ;

        }

        // Read each line and add it content to tickerList object (in memory)
        DecodeTickerCSV( str ) ;

    }

    // close the file
    textfile.close() ;

    // Create Candles from tickerList information.
    CreateCandles() ;

    // Save Candles into CSV files.
    SaveCandles( outputfolder ) ;

}

// auxiliary function to "parse" csv line and extract column values
string TickerToCandleCtrl::currentColumn( const string &pstr,
                                          int &ppos ) {

    int lpos = pstr.find( ";", ppos ) ;

    string result ;

    if ( lpos != 0 ) {

        result = pstr.substr( ppos, lpos - ppos ) ;

    } else {

        result = pstr.substr( ppos + 1, pstr.size() - ppos ) ;

    }

    ppos = lpos + 1 ;

    return result ;

}

// Adds ticker item into tickerList and fills attributes according to CSV line
void TickerToCandleCtrl::DecodeTickerCSV( const string &pstr ) {

    int lpos = 0 ;

    Ticker* ticker = dynamic_cast<Ticker*>( tickerlist->Add() ) ;

    ticker->settstext ( currentColumn( pstr, lpos ) ) ;
    ticker->setsymbol ( currentColumn( pstr, lpos ) ) ;
    ticker->setticker ( currentColumn( pstr, lpos ) ) ;
    ticker->setvalue  ( round( stof( currentColumn( pstr, lpos ) ) * 100 ) / 100 ) ;

}

// Reads tickers and creates theirs candle list (5 seconds and 1 minute) for each Asset
void TickerToCandleCtrl::CreateCandles() {

    // full loop (creation of 5s candles)
    for (int i = 0; i < tickerlist->Count(); i++) {

        // get item from index
        Ticker* ticker = dynamic_cast<Ticker*>( tickerlist->GetItem( i ) ) ;

        // ByName automatically creates and item for a new asset and then executes ComputeTicker.
        dynamic_cast<AssetCandles*>( acl->ByName( ticker->getsymbol(), true ) )->ComputeTicker( ticker ) ;

    }

    // creating 1 minute candles from 5 seconds candles is faster than
    // creating 1 minute candles from tickers
    for (int i = 0; i < acl->Count(); i++) {

        dynamic_cast<AssetCandles*>( acl->GetItem( i ) )->Create1mCandles() ;

    }

    acl->FeedMainCandles() ;

}

// Save Candle List to File Name (Includes Symbol as first column)
void TickerToCandleCtrl::SaveToCSVFile( const CandleList* &pcandlelist,
                                        const string &psymbol,
                                        const string &pfilename ) {

    // create file
    ofstream filetext( pfilename ) ;

    const char aspas = '\"' ;

    filetext << "\"symbol\";\"from\";\"to\";\"open\";\"close\";\"high\";\"low\";\"volume\"" << endl ;

    // write lines
    for (int i = 0; i < pcandlelist->Count(); i++) {

        Candle* candle = dynamic_cast<Candle*>( pcandlelist->GetItem( i ) ) ;

        filetext << aspas + candle->getsymbol()         + "\";" +
                    candle->gettsopen().getText()       + ";"   +
                    candle->gettsclose().getText()      + ";"   +
                    FloatToStr( candle->getopen(), 2 )  + ";"   +
                    FloatToStr( candle->getclose(), 2 ) + ";"   +
                    FloatToStr( candle->gethigh(), 2 )  + ";"   +
                    FloatToStr( candle->getlow(), 2 )   + ";"   +
                    to_string( candle->getvolume() )   << endl ;

    }

    filetext.close() ;

}

// Creates directories and save Candle List to File Name
void TickerToCandleCtrl::SaveCandlesToFile( const string &pname,
                                            const CandleList* &pcandlelist,
                                            const string &poutputfolder ) {

    const string symbol = pname ;

    string loutputfolderroot = putBarra( poutputfolder ) ;

    CreateDirectory( loutputfolderroot ) ;

    // this procedure can be called by 2 places:
    // 1. Asset's Candle List (symbol has a value)
    // 2. Total's Candle List (blank symbol)
    if ( symbol != "" ) {

        string loutputfolder = putBarra( loutputfolderroot + symbol ) ;

        CreateDirectory( loutputfolder ) ;

        string filename = loutputfolder + symbol + "candles" + ( pcandlelist->getintervalMS() == 5000 ? "_5s" : "_1m"  ) + ".csv" ;

        SaveToCSVFile( pcandlelist, symbol, filename ) ;

    } else {

        string filename = loutputfolderroot + "allcandles" + ( pcandlelist->getintervalMS() == 5000 ? "_5s" : "_1m"  ) + ".csv" ;

        SaveToCSVFile( pcandlelist, symbol, filename ) ;

    }


}

// Save 5s and 1min candle list for each asset
void TickerToCandleCtrl::SaveCandles( const string &poutputfolder ) {

    // loop for each asset
    for (int i = 0; i < acl->Count(); i++) {

        const AssetCandles* assetcandles = dynamic_cast<AssetCandles*>( acl->GetItem( i ) ) ;

        const string symbol = assetcandles->getName() ;

        const CandleList* c5s = assetcandles->getCandleList5s() ;

        // Saves 5s candles for asset
        SaveCandlesToFile( symbol,
                           c5s,
                           poutputfolder ) ;

        const CandleList* clm = assetcandles->getCandleList1m() ;

        // Saves 1min candles for asset
        SaveCandlesToFile( symbol,
                           clm,
                           poutputfolder ) ;

    }

    const CandleList* allcandles5S = acl->getmaincandlelist5s() ;

    string psymbol = "" ;

    // Saves total's 5s candles
    SaveCandlesToFile( psymbol,
                       allcandles5S,
                       poutputfolder ) ;

    const CandleList* allcandles1m = acl->getmaincandlelist1m() ;

    // Saves total's 1min candles
    SaveCandlesToFile( psymbol,
                       allcandles1m,
                       poutputfolder ) ;

}

// Creates ticketList and acl upon construction
TickerToCandleCtrl::TickerToCandleCtrl() {

    tickerlist       = new TickerList() ;
    acl              = new AssetCandlesList() ;

}

// Destroys ticketList and acl upon destruction
TickerToCandleCtrl::~TickerToCandleCtrl() {

    delete tickerlist ;
    delete acl        ;

}



