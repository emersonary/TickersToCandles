//---------------------------------------------------------------------------

#pragma once

#ifndef uAuxH
#define uAuxH
//---------------------------------------------------------------------------
#endif

#include <string>

using namespace std ;

// return path name from full file name
string getPathName(const string& s) ;

// returns "\" at the end of a string in case it is not already there
string putBarra( const string &str ) ;

// create direction if it does not exist
void CreateDirectory( const string &folder ) ;

// Convert float into string using given decimal places
string FloatToStr( double number, int decimals) ;

// Right Pad
string padTo( const string &str, const size_t num, const char paddingChar = ' ' ) ;
