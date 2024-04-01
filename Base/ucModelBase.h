//---------------------------------------------------------------------------

/*
#pragma hdrstop

*/

#pragma once

#ifndef ucModelBaseH
#define ucModelBaseH

#include <string>
#include <vector>

using namespace std ;

//---------------------------------------------------------------------------
#endif

class ITList ;

// class to represent an item.
// everything is an "IT". the "IT" do not have to be contained in a list.
// every class sd be inherited from "IT".
class IT {
private :

    // Constructors cannot execute virtual methods (that sucks)
    // so I had to divide Init Execution in 2 methods.
    // This one is executed by constructors reassuring there is no duplicated executions
    // ( Init() can be executed outside constructors, and they are overriden along the derived classes)
    // Every derived class sd explicitly call InitStatic() upon construction.
    void InitStatic() {} ;

protected:

    // variable to hold class owner
    // each object (including every descendent) holds his owner (can be nullptr)
    IT* vowner ;

public :

    // constructor with "owner" parameter
    IT( IT* powner = nullptr ) ;

    // public getter for owner
    IT* getOwner() const ;

    // public setter for owner
    void setOwner( IT* pOwner ) ;

    // function to be called upon construction
    virtual void Init() ;

};

// class that holds list of items.
// "ITList" is also an "IT".
class ITList : public IT {
private:

    // vector to hold items of this list
    vector<IT*> lst ;

protected:

    // function that has to be overriden so it can create the descendent IT class.
    virtual IT* getnewIT() ;

public:

    ITList( IT* powner = nullptr ):IT( powner ) {} ;

    ~ITList() ;

    // Returns the quantity of items in memory
    int Count() const ;

    // pIT can be null (create owner and take ownership or
    // it can have a pointer created by other list.
    virtual IT* Add( IT* pIT = nullptr ) ;

    // Initializes the attributes of the object
    // according to its custom behaviours
    // (Example ID = -1)
    void Init() override {

       IT::Init() ;

    } ;

    // Delete Item
    void Delete( const int &pIndex ) ;

    // Clear Items
    void Clear() ;

    // Return the item of a given index.
    IT* GetItem( const int &pIndex ) const ;

    // Returns the first item
    IT* First() ;

    // Returns the last item
    IT* Last() ;


};

