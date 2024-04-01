//---------------------------------------------------------------------------

#pragma once

#ifndef ucCtrlTickersToCandlesH
#define ucCtrlTickersToCandlesH
//---------------------------------------------------------------------------

#include <fstream>
#include <iostream>

#include "ucModelAsset.h"
#include "ucModelTicker.h"
#include "ucModelCandles.h"

#endif


class TickerToCandleCtrl {

private:

    // Holds the class that reads TickersList (raw) file.
    TickerList* tickerlist ;

    // Class to read tickers list and split into its assets
    AssetCandlesList* acl ;

    // auxiliary function to "parse" csv line and extract column values
    string currentColumn( const string &pstr,
                          int &ppos ) ;

    // Adds ticker item into tickerList and fills attributes according to CSV line
    void DecodeTickerCSV( const string &pstr ) ;

    // Reads tickers and creates theirs candle list (5 seconds and 1 minute) for each Asset
    void CreateCandles() ;

    // Save Candle List to File Name (Includes Symbol as first column)
    void SaveToCSVFile( const CandleList* &pcandlelist,
                        const string &psymbol,
                        const string &pfilename ) ;

    // Creates directories and save Candle List to File Name
    void SaveCandlesToFile( const string &pname,
                            const CandleList* &pcandlelist,
                            const string &poutputfolder ) ;

    // Save 5s and 1min candle list for each asset
    void SaveCandles( const string &poutputfolder ) ;

public:

    TickerToCandleCtrl() ;

    ~TickerToCandleCtrl() ;

    // method to read tickers and mounts candles into memory
    void ExecTickersToCandles() ;

};

    
