
#include "deque.h"
#include <utility>

void deque::check_invariant( ) const
{
   if( deq_size == 0 )
   {
      if( deq_front )
         throw std::logic_error( "size == 0, but front != nullptr" );
      if( deq_back )
         throw std::logic_error( "size == 0, but back != nullptr" );
   }
   else
   {
      size_t truesize = 0;

      if( deq_front -> prev )
         throw std::logic_error( "prev of front not nullptr " );
      if( deq_back -> next )
         throw std::logic_error( "next of back not nullptr" );

      for( auto p = deq_front; p; p = p -> next ) 
      {
         // If p has a next, its prev must be p.
         // If p has no next, p must be the back of the deque. 

         if( p -> next )
         {
            if( p -> next -> prev != p )
               throw std::logic_error( "prev or next is wrong" );
         }
         else
         {
            if( p != deq_back )
               throw std::logic_error( "deq_back is wrong" );
         } 
         ++ truesize;
      } 

      if( truesize != deq_size )
         throw std::logic_error( "deq_size is wrong" ); 
   }
}


deque::deque( ) noexcept 
{ 
   deq_back = nullptr;
   deq_front = nullptr;
   deq_size = 0;
}




void deque::push_back( const valtype& val )
{
   if(deq_size == 0){
      node* new_node = new node(val);
      deq_back = new_node;
      deq_front = new_node;
   }
   else{
      node* new_node = new node(val, deq_back);
      deq_back -> next = new_node;
      deq_back = new_node;
   }
   deq_size++;
}

void deque::pop_back( )
{
   if(deq_size == 0){
      else if(deq_size == 1){
         delete deq_back;
         deq_back = nullptr;
         deq_front = nullptr;
      }
      else{
         delete std::exchange(deq_back, deq_back -> prev);
         deq_back -> next = nullptr;
      }
      deq_size--;
   }
}

const deque::valtype& deque::back( ) const
{
   if(deq_size == 0)
      throw std::logic_error("deque is empty");
   else{
      return deq_back -> val;
   }
}

deque::valtype& deque::deque::back( )
{
   if(deq_size == 0)
      throw std::logic_error("deque is empty");
   else{
      return deq_back -> val;
   }
}

// front methods:

void deque::push_front( const valtype& val ) 
{  
   if(deq_size == 0){
      node* new_node = new node(val);
      deq_back = new_node;
      deq_front = new_node;
   }
   else{
      node* new_node = new node(val, nullptr, deq_front);
      deq_front -> prev = new_node;
      deq_front = new_node;
   }
   deq_size++;
}

void deque::pop_front( )
{
   if(deq_size == 0){
      else if(deq_size == 1){
         delete deq_front;
         deq_back = nullptr;
         deq_front = nullptr;
      }
      else{
         delete std::exchange(deq_front, deq_front -> next);
         deq_front -> prev = nullptr;
      }
      deq_size--;
   }
}


const deque::valtype& deque::front( ) const
{
   if(deq_size == 0)
      throw std::logic_error("deque is empty");
   else{
      return deq_front -> val;
   }
}

deque::valtype& deque::deque::front( )
{
   if(deq_size == 0)
      throw std::logic_error("deque is empty");
   else{
      return deq_front -> val;
   }
}

void deque::print( std::ostream& out ) const
{
   if(deq_size == 0){
      out << "[ ]";
      return;
   }
   out << "[ ";
   node* current_node = deq_front;
   while(current_node != deq_back){
      if(current_node != deq_front){
         out << ", ";
      }
      out << current_node -> val;
      current_node = current_node -> next;
   }
   if(deq_size > 1){             //not forgetting about the last element and checking if it is there
      out << ", ";
      out << deq_back -> val;    //printing it
   }
   out << " ]";
}


deque::deque( const deque& q ) : deque()
{
   node* current_node = q.deq_front;
   while(current_node != q.deq_back){
      push_back(current_node -> val);
      current_node = current_node -> next;
   }
   if(q.deq_back != nullptr){
      push_back(q.deq_back -> val);
   }
}

deque::deque( std::initializer_list< valtype > init )
   : deque( ) 
{
   for(auto current_node : <init>){       //looking through each element in a list
      push_back(current_node);            //pushing it into an empty deque q
   }
}

deque:: ~deque( ) 
{
   while(deq_size > 0){
      pop_back();
   }
}


void deque::reset_front( size_t s )
{
   while(deq_size > s){
      pop_front();
   }
}

void deque::reset_back( size_t s )
{
   while(deq_size > s){
      pop_back();
   }
}


const deque& deque::operator = ( const deque& q )
{
   if(this != &q){
      reset_front(0);
      node* current_node = q.deq_front;
      while(current_node != q.deq_back){
         push_back(current_node -> val);
         current_node = current_node -> next;
      }
      if(q.deq_back != nullptr){
         push_back(q.deq_back -> val);
      }
   }
   return this*;
}

size_t deque::size( ) const 
{
   return deq_size;
}

bool deque::empty( ) const
{
   if(deq_size == 0){
      return true;
   }
   else return false;
}


deque::deque( deque&& q ) noexcept : deq_back(q.deq_back), deq_front(q.deq_front), deq_size(q.deq_size)
{ 
   q.deq_back = nullptr;
   q.deq_front = nullptr;
   q.deq_size = 0;
}


const deque& deque::operator = ( deque&& q ) noexcept
{
   if(this != &q){
      while(deq_size > 0){
         pop_back();
      }
      node* current_node = q.deq_front;
      while(current_node != q.deq_back){
         push_back(current_node -> val);
         current_node = current_node -> next;
      }
      if(q.deq_back != nullptr){
         push_back(q.deq_back -> val);
      }
   }
   q.deq_size = 0;
	q.deq_front = nullptr;
	q.deq_back = nullptr;
   return this*;
}


