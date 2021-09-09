//CS311 Yoshii
//INSTRUCTION:
//Llist class - header file template 
//You must complete the ** parts and then complete llist.cpp
//Don't forget PURPOSE and PARAMETERS 

// =======================================================
// HW#: HW3P1 llist
// Your name: Olaf Zielinski
// Compiler:  g++ 
// File type: headher file  llist.h
//=======================================================

// alias el_t : element type definition
typedef int el_t;

//a list node is defined here as a struct Node for now
struct Node
{
  el_t Elem;   // elem is the element stored
  Node *Next;  // next is the pointer to the next node
};
//---------------------------------------------------------

class llist
{
  
 private:
  Node *Front;       // pointer to the front node
  Node *Rear;        // pointer to the rear node
  int  Count;        // counter for the number of nodes
  
 public:

  // Exception handling classes 
  class Underflow{};
  class OutOfRange{};  // thrown when the specified Node is out of range

  llist ();     // constructor to create a list object
  ~llist();     // destructor to destroy all nodes
  
  //Return true if both front and rear are NULL & Count == 0. That means list is empty.
  bool isEmpty();
    
  //Display all elements in the list. 
  void displayAll();

  //add a new node at the front of the list. Element is being sent to function. 
  void addFront(el_t);
    
  //add a new node at the end of the list. Send the element to function to add it.
  void addRear(el_t);

  //delete the element at the front of the list. Send the element by reference back to the main.
  void deleteFront(el_t&);
    
  //delete the element at the end of the list. Send the elemenet back by reference to the main. 
  void deleteRear(el_t&);
    
  //delete the element at specific index. Send the index to function, and get the element back by ref. 
  void deleteIth(int, el_t&);

  //insert an element at specific index. Send the index to function, and the element to insert. 
  void insertIth(int, el_t);

  //Copy Constructor to allow pass by value and return by value
  llist(const llist&);
  
  //Overloading of = 
  llist& operator=(const llist&);

};
