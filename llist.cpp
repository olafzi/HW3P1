//CS311 Yoshii Linked List class
//INSTRUCTION:
//Must use the provided HW3P1_help.doc to create llist.cpp
//It helps to first create if-then-else structure to fill in later.
//- Make sure PURPOSE and PARAMETER comments are given in detail
//- Make sure all if-then-else are commented describing which case it is
//- Make sure all local variables are described fully with their purposes
//EMACS HINT:
//  You can copy from a Word document to emacs (contrl-right click)
//  control-K cuts and control-Y pastes
//  Esc x replace-str does string replacements
//  Esc > goes to the end of the file; Esc < to the beginning
//  Tab on each line will indent perfectly for C++

// ====================================================
//HW#: HW3P1 llist
//Your name: Olaf Zielinski
//Complier:  g++
//File type: llist.cpp implementation file
//=====================================================

using namespace std;
#include<iostream>
#include"llist.h" 

llist::llist()
{Front = Rear = NULL; Count = 0; }

llist::~llist() {
  cout << "Deleting all pointers";
  el_t num;
  while(!isEmpty()) {
      deleteFront(num);
    }
}

//PURPOSE:Checks if the list is empty and return true if front & back
//== NULL & Count=0.
//PARAMETER: nothing is sent
bool llist::isEmpty() {
  return Front == NULL && Rear == NULL && Count == 0;
}

//PURPOSE:Display all the elements in all the nodes.
//PARAMETER: nothing is sent
void llist::displayAll() {
  if(isEmpty())
    cout << "The list is empty." << endl;
  else{
    Node *P = Front;
    while (P != NULL) {
      cout << "|" << P->Elem << "| ";
      P = P->Next;
    }
    cout << endl;
  }
}

//PURPOSE:add a new node to the rear of the list.
//PARAMETER:The element to be added to the rear.
void llist::addRear(el_t NewNum) {
  //check if it's the first element, if true, add to front.
  if (Front == NULL) { 
    Front = new Node; //link the front to the new Node
    Rear = Front;
  }else{ //else, add it to the end of the list
    Rear->Next = new Node; //link next of last to the new node
    Rear = Rear->Next; //& the rear is the rear-next.
  }
  Rear->Elem = NewNum; //add the element to the node
  Rear->Next = NULL; //set next as NULL
  Count++; //and increase counter
}

//PURPOSE:add a new node to the front of the list.
//PARAMETER:The element to be added to the front. 
void llist::addFront(el_t NewNum) {
  //check if it's the first element, if true, add to front.
  if(Front == NULL) {
    Front = new Node; //link the front to the new Node
    Front->Elem = NewNum; //add the element to the node
    Front->Next = NULL; //set next to NULL
    Rear = Front; //and rear is at the same place.
  }else{ //else, add it to the front of the list
    Node *x; //make a dummy pointer
    x = new Node; // link it to the new node
    x->Next = Front; //set the next equal to front
    Front = x; //and connect front to the node.
    Front->Elem = NewNum; //then add element to the node.
  }
  Count++; //and lastly, increase counter.
}

//PURPOSE: delete the first node.
//PARAMETER:pass the variable by reference back to the main
void llist::deleteFront(el_t& OldNum) {
  //check if empty, if yes, throw underflow. 
  if(isEmpty())
    throw Underflow();
  //otherwise, check if there is only one element, if so
  //delete the front, set front and rear to NULL and make list empty.
  else if(Count == 1){
    OldNum = Front->Elem;
    delete Front;
    Front = NULL;
    Rear = NULL;
    Count--;
    //otherwise, delete the first node
  }else{
    OldNum = Front->Elem; //oldnum gets the element from front.
    Node *Second; //make a dummy pointer
    Second = Front->Next; //set it to the 2nd node
    delete Front; //delete the front
    Front = Second; //set the front from second
    Count--; //decrease the counter. 
  }
}

//PURPOSE:delete the last node. 
//PARAMETER:pass the variable by reference back to the main. 
void llist::deleteRear(el_t& OldNum) {
  //check if empty, if yet, throw underflow
  if(isEmpty())
    throw Underflow();
  //otherwise, check if there is only one element, if so
  //delete the rear, set front & rear to NULL and make list empty.
  else if(Count==1){
    OldNum = Rear->Elem;
    delete Rear;
    Front = NULL;
    Rear = NULL;
    Count--;
    //otherwise, delete the last node same way as the front, but the rear.
  }else{
    OldNum = Rear->Elem;
    Node *p = Front;
    while(p->Next != Rear)
      p = p->Next;
    delete Rear;
    Rear = p;
    Rear->Next = NULL;
    Count--;
  }
}

//PURPOSE: delete the element at the index x.
//PARAMETER: the index of the element to be deleted. variable passed by ref.
void llist::deleteIth(int I, el_t& OldNum) {
  //first, check if the index is out of range- if true, throw outofrange.
  if (I > Count || I<1)
    throw OutOfRange();
  else if(I == 1) //otherwise, if first is to be deleted, call deletefront
    deleteFront(OldNum);
  else if(I == Count) // if last to be deleted, call deleterear
    deleteRear(OldNum);
  else { //otherwise, it has to be in the middle, so
    Node *P = Front; //make a new dummy pointer, set to front
    Node *Pdel = Front->Next; //and one to delete the element
    for (int x=1; x<=I-1; x++){ //traverse list until find the I-1
      P = P->Next; //set the pointer to the next
      Pdel = Pdel->Next; //and Pdel to it's next. 
    }
    P->Next = Pdel->Next; //then, link the two
    OldNum = Pdel->Elem; //copy the element to oldnum
    delete Pdel; //delete the node
    Count--; //decrease the counter
  }
}

//PURPOSE: add the element at the index x.
//PARAMETER: the index of the element to be added. variable passes by ref.
void llist::insertIth(int I, el_t newNum) {
  //first, check if the index is out of range - if true, throw outofrange.
  if(I>Count+1 || I < 1)
    throw OutOfRange();
  else if(I == 1) //otherwise, if first is to be added, call addfront
    addFront(newNum);
  else if(I==Count+1) //and if last to be added, call addrear.
    addRear(newNum);
  else{ //otherwise, it has to be in the middle, so
    Node *P = Front; //make a new dummy pointer, set to front
    for(int x=1; x <= I-1; x++){ //traverse list until find I-1
      P = P->Next; //set P to it's next node.
    }
    Node *tmp = P->Next; //temporary pointer set to the next node.
    P->Next = new Node; //make a new Node and link it to P next's.
    P->Next->Next = tmp; //link the two lists back
    P->Next->Elem = newNum; //insert to that element.
    Count++; //increase the counter.
  }
 }

//PURPOSE:Copy overload function that will copy the paramenter and functions values & return it.
//PARAMETER:
llist::llist(const llist& Original) {
  Front= NULL;  Rear = NULL; Count=0;
  Node *P = Original.Front;  // local pointer for Original
  while (P != NULL)  // a loop which repeats until you reach the end of OtherOne. 
    {
      this->addRear(P->Elem);//P’s element is added to this->
      P = P->Next;           // Go to the next node in OtherOne   
    }
}


//PURPOSE:to allow client to use = for llist by copying and adding the value to the list.
//PARAMETER:
llist& llist::operator=(const llist& OtherOne) {
  el_t x;
  if (&OtherOne != this){
    while (!this->isEmpty())
      this->deleteRear(x);
    Node *P; //Local pointer for OtherOne
    P=OtherOne.Front;
    while(P!= NULL){ //loop, keep repeating until end of OtherOne
      this->addRear(P->Elem); //P's element is added to this
      P = P->Next; //go to next node in OtherOne
    }
  }
    return *this;
} //end if

