//
// demoes list template usage
//
// Mikhail Nesterenko
// Modified by: Zaz Brown
//

#include <iostream>
#include <memory>
#include "list.hpp" // list template

using std::cout; using std::endl;

int main(){
   std::shared_ptr<node<int>> head, currentPtr;

   //
   // integer list manipulation
   //

   // first node
   head = std::make_shared<node<int>>();
   head->setData(1);

   currentPtr = std::make_shared<node<int>>();  // second node
   currentPtr->setData(2);

   head->setNext(currentPtr); // list contains two nodes

   cout << head->getData() << " "; // printing head node

   // deallocating head node
   currentPtr = head;
   head = head->getNext();

   // printing and deallocating the last element
   cout << head->getData() << endl;


   //
   // character list manipulation
   //

   // allocating head node
   auto charHead = std::make_shared<node<char>>();
   auto current = charHead;
   current->setData('A');

   // creating list
   for(char letter = 'B'; letter <= 'Z'; ++letter){
      auto const newNode = std::make_shared<node<char>>();
      newNode->setData(letter);
      current->setNext(newNode);
      current = newNode;
   }

   for(current = charHead;  current != nullptr; current=current->getNext())
     cout << current->getData() << ' ';
   cout << endl;

   // deallocate list
   current = charHead;
   while(current != nullptr){
      charHead = charHead->getNext();
      current = charHead;
   }
}
