//---------------------------------------------------------------------------

#pragma hdrstop
#pragma once

#include "uAux.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


#include <filesystem>
#include <sstream>
#include <iomanip>

namespace fs = std::filesystem;

// create direction if it does not exist
void CreateDirectory( const string &folder ) {

 fs::create_directory( folder ) ;

}

// Convert float into string using given decimal places
string FloatToStr( double number, int decimals) {
    stringstream stream;
    stream << fixed << setprecision(decimals) << number;
    return stream.str();
}

// Right Pad
string padTo( const string &str, const size_t num, const char paddingChar )
{
    string result = str ;

    if(num > result.size())
        result.insert(0, num - result.size(), paddingChar);

    return result ;
}

// return path name from full file name
string getPathName(const string& s) {

   char sep = '/';

#ifdef _WIN32
   sep = '\\';
#endif

   size_t i = s.rfind(sep, s.length());
   if (i != string::npos) {
      return(s.substr(0, i));
   }

   return("");
}

// returns "\" at the end of a string in case it is not already there
string putBarra( const string &str ) {

    if (!str.empty() && ( str[ str.length() - 1 ] != '\\' ) ) {

        return str + "\\" ;

    }

    return str ;

}
