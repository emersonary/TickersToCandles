//---------------------------------------------------------------------------

#pragma once

#ifndef ucModelCadH
#define ucModelCadH
//---------------------------------------------------------------------------

#include <string>
#include <vector>
#include "ucModelBase.h"

#endif

// class ITId = IT with ID and Name attributes
class ITId : public IT {
private:

    int    vId   ; // ID attribute
    string vName ; // Name attribute

    // initializes vId = -1 ;
    void InitStatic() ;

public:

    ITId( IT* powner = nullptr ):IT( powner ) {

        InitStatic() ;

    } ;

    // class InitStatic
    void Init() override ;

    // getters
    int getId() const ;
    string getName() const ;

    // setters
    void setId( const int &pId ) ;
    void setName( const string &pName ) ;

};

class ITIdList : public ITList {
protected:

    // creates ITId class and returns it as "IT"
    IT* getnewIT() override ;

    // returns the index of a Name (position of the item within the list. first = 0).
    int IndexOfName( const string &pname ) ;

    // returns the index of an Id (position of the item within the list. first = 0).
    int IndexOfId( const int &pId ) ;

public:

    ITIdList( IT* powner = nullptr ): ITList( powner ) {} ;

    // returns the object item of a given name.
    // if pcreating == true, creates it when name does not exist
    ITId* ByName( const string &pname, const bool &pcreating = false ) ;

    // returns the object item of a given name.
    // if pcreating == true, creates it when name ID not exist
    ITId* ById( const int &pid, const bool &pcreating = false ) ;

} ;



