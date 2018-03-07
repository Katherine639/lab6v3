#include "iterator.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
The OperatorIterator will be used to iterate over composite nodes with two children. This means it's first will initialize to the left child, 
and its next will cycle from left child (which is where it is set to start), to right child, then to NULL.*/

OperatorIterator::OperatorIterator(Base* ptr): Iterator(ptr){}

void OperatorIterator::first() {
    current_ptr = self_ptr->get_left();
}

void OperatorIterator::next() {
    if( current_ptr == self_ptr->get_left() ) {
        current_ptr = self_ptr->get_right();
    }
    else if( current_ptr == self_ptr->get_right() ) {
        current_ptr = NULL;
    }
}

bool OperatorIterator::is_done() {
    // Return true if there are no more elements on the stack to iterate
    if( current_ptr == NULL )
        return true;
    else
        return false;
}

Base* OperatorIterator::current() {
    // Return the current for the top iterator in the stack
    return current_ptr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
The UnaryIterator will be used to iterate over composite nodes with one child (only Sqr in our case). 
This means it's first will initialize to the only child (which has been redeclared in the composite class as the left child, 
with Unary having no right child to make for an easier interface, 
and next will cycle from child (which is where it is set to start) to NULL.*/

UnaryIterator::UnaryIterator(Base* ptr): Iterator(ptr){}

void UnaryIterator::first() {
    current_ptr = self_ptr->get_left();
}

void UnaryIterator::next() {
    current_ptr = NULL;
}

bool UnaryIterator::is_done() {
    // Return true if there are no more elements on the stack to iterate
    if( current_ptr == NULL )
        return true;
    else
        return false;
}

Base* UnaryIterator::current() {
    // Return the current for the top iterator in the stack
    return current_ptr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

NullIterator::NullIterator(Base* ptr): Iterator(ptr){}

void NullIterator::first() {
    return;
}

void NullIterator::next() {
    return;
}

bool NullIterator::is_done() {
    return true;
}

Base* NullIterator::current() {
    return NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PreorderIterator::PreorderIterator(Base* ptr): Iterator(ptr){}

void PreorderIterator::first() {
    // Empty the stack (just in case we had something leftover from another run)
    // Create an iterator for the Base* that we built the iterator for
    // Initialize that iterator and push it onto the stack
    while ( !iterators.empty() ){
        iterators.pop();
    }
    Iterator* temp = self_ptr->create_iterator();
    temp->first();
    iterators.push( temp );
    //delete temp;
    
    
}

void PreorderIterator::next() {
    // Create an iterator for the item on the top of the stack
    // Initialize the iterator and push it onto the stack
    // As long as the top iterator on the stack is_done(), pop it off the stack and then advance whatever iterator is now on top of the stack

    Iterator* temp = iterators.top()->current()->create_iterator();
    temp->first();
    iterators.push( temp );
    
    while( !iterators.empty() && iterators.top()->is_done() ){
        iterators.pop();
        
        if( iterators.empty() ) break;
        
        iterators.top()->next();
    }
    //delete temp;
}

bool PreorderIterator::is_done() {
    // Return true if there are no more elements on the stack to iterate
    return iterators.empty();
}

Base* PreorderIterator::current() {
    // Return the current for the top iterator in the stack
    if( iterators.empty() ) return NULL;
    
    return iterators.top()->current();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
