//---------------------------------------------------------------------------

#include "ucModelBase.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


// Returns the quantity of items in memory
int  ITList::Count() const {

    return lst.size() ;

}

// Overridable function to create descendent of IT class
IT* ITList::getnewIT() {

 return new IT( this ) ;

} ;

// pIT can be null (create owner and take ownership or
// it can have a pointer created by other list.
IT* ITList::Add( IT* pIT )
 {

     IT* result ;

     if ( pIT == nullptr) {

         result = getnewIT() ;


     } else {

        result = pIT ;

        if ( result->getOwner() == nullptr ) {

            result->setOwner( this ) ;

        }

     }

     lst.push_back( result ) ;

     return result ;

 }

// Delete Item
void ITList::Delete( const int &pIndex )
 {

      // check if owner of item is this instance.
     const bool lowner = GetItem( pIndex )->getOwner() == this ;

     // if so, free item (delete from memory)
     if ( lowner ) {

         delete GetItem( pIndex ) ;

     }

     // delete item from vector
     lst.erase( lst.begin() + pIndex ) ;

 }

// Clear Items
void ITList::Clear( )
{

     while ( Count() > 0 )
         Delete( Count() - 1 ) ;


}

// returns the item pointer
IT* ITList::GetItem( const int &pIndex ) const {

  return lst[ pIndex ] ;

}

// returns the first item ;
IT* ITList::First() {

 if (Count() > 0 ) {

     return GetItem( 0 ) ;

 }

 return nullptr ;

}

// returns the last item ;
IT* ITList::Last() {

 if ( Count() > 0 ) {

     return GetItem( Count() - 1 ) ;

 }

 return nullptr ;

}

// constructor from IT. Initializes the owner variable and Exec InitStatic() ;
IT::IT( IT* powner ) {

    vowner = powner ;
    InitStatic() ;

}

// returns de owner (pointer)
IT* IT::getOwner() const {


    return vowner ;

}

// sets the Owner
void IT::setOwner( IT* pOwner ) {

    vowner = pOwner ;

}

// Initializes the item. It is overridable and can be executed after construction.
void IT::Init() {

    InitStatic() ;

}

// Clear Items upon destruction
ITList::~ITList() {

  Clear() ;

}
