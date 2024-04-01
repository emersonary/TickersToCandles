//---------------------------------------------------------------------------

#include "ucModelCad.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

// initializes vId = -1 ;
void ITId::InitStatic() {

    vId   = -1 ;
    vName = "" ;

} ;

// class InitStatic
void ITId::Init() {

    IT::Init() ;

    InitStatic() ;

}

// getter
int ITId::getId() const {

    return vId ;

} ;

// getter
string ITId::getName() const {

    return vName ;

} ;

// setter
void ITId::setId( const int &pId ) {

    vId = pId ;

}

// setter
void ITId::setName( const string &pName ) {

    vName = pName ;

}

// creates ITId class and returns it as "IT"
IT* ITIdList::getnewIT() {

 return new ITId( this ) ;

} ;

// returns the index of a Name (position of the item within the list. first = 0).
int ITIdList::IndexOfName( const string &pname ) {

    for ( int i = 0; i < Count() ; i++) {

        ITId* item = dynamic_cast<ITId*>( GetItem( i ) ) ;

        if ( item->getName() == pname ) {

            return i ;

        }
    }

    return -1 ;

}

// returns the index of an Id (position of the item within the list. first = 0).
int ITIdList::IndexOfId( const int &pId ) {

    for ( int i = 0; i < Count() ; i++) {

        ITId* item = dynamic_cast<ITId*>( GetItem( i ) ) ;

        if ( item->getId() == pId ) {

            return i ;

        }
    }

    return -1 ;

}

// returns the object item of a given name.
// if pcreating == true, creates it when name does not exist
ITId* ITIdList::ByName( const string &pname, const bool &pcreating ) {

    int lindex = IndexOfName( pname ) ;

    if ( lindex != -1 ) {

        return dynamic_cast<ITId*>( GetItem( lindex ) ) ;

    }  else {

        if ( pcreating ) {

            ITId* result = dynamic_cast<ITId*>( Add() ) ;

            result->setName( pname ) ;

            return result ;

        } else {

            return nullptr ;

        }

    }


}

// returns the object item of a given name.
// if pcreating == true, creates it when name ID not exist
ITId* ITIdList::ById( const int &pid, const bool &pcreating ) {

    int lindex = IndexOfId( pid ) ;

    if ( lindex != -1 ) {

        return dynamic_cast<ITId*>( GetItem( lindex ) ) ;

    }  else {

        if ( pcreating ) {

            ITId* result = dynamic_cast<ITId*>( Add() ) ;

            result->setId( pid ) ;

            return result ;

        } else {

            return nullptr ;

        }

    }


}
