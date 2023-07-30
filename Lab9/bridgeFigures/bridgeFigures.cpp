// filled/hollow figures demonstrates Bridge Design Pattern,
// square is either hollow or square and is painted with a particular character,
// it is bridged over Figure --> Fill abstract body/handle
// Mikhail Nesterenko
// Modified by Zaz Brown

#include <iostream>

using std::cout; using std::endl; using std::cin;

// Hollow and Filled naturally (in terms of DRY) inherit from FullyFilled, so
// there is no need for an abstract Fill class
class FullyFilled {
public:
   FullyFilled(char borderChar, char fillChar):
      fillChar_(fillChar), borderChar_(borderChar){}
   virtual char getBorder() {return borderChar_;}
   virtual char getInternal() {return fillChar_;}
   ~FullyFilled() {}
protected:
   char fillChar_;
   char borderChar_;
};

class Hollow: public FullyFilled {
public:
   Hollow(char borderChar):FullyFilled(borderChar, ' '){}
   // duplication of code is avoided here and below
};

class Filled: public FullyFilled {
public:
   Filled(char bothChar):FullyFilled(bothChar, bothChar){}
};

class RandomFilled: public FullyFilled {
public:
   RandomFilled(char borderChar, char fillChar):
      FullyFilled(borderChar, fillChar){}
   char getBorder() override {
      return rand()%2==0 ? borderChar_ : fillChar_;
   }
   char getInternal() override {
      return rand()%2==0 ? borderChar_ : fillChar_;
   }
};

// abstract handle
class Figure {
public:
   Figure(int size, FullyFilled* fill): size_(size), fill_(fill){}
   virtual void draw() =0;
   virtual ~Figure(){}
protected:
   int size_;
   FullyFilled *fill_;
};

// concrete handle
class Square: public Figure {
public:
   Square(int size, FullyFilled* fill): Figure(size, fill){}
   void draw() override;

};

void Square::draw() {
   for(int i=0; i < size_; ++i){
      for(int j=0; j < size_; ++j)
         if(i==0 || j==0 || i==size_-1 || j==size_-1 )
            cout << fill_ -> getBorder();
         else
            cout << fill_ -> getInternal();
      cout << endl;
   }
}

int main() {

   /*
   FullyFilled* hollowPaintJ = new Hollow('J');
   FullyFilled* filledPaintStar = new Filled('*');


   Figure *smallBox = new Square(5, hollowPaintJ);
   Figure *bigBox = new Square(15, filledPaintStar);

   smallBox->draw();
   cout << endl;
   bigBox -> draw();

   */

   // ask user for figure parameters
   cout << "Enter border character: ";
   char bchar; cin >> bchar;

   cout << "Enter fill character: ";
   char fchar; cin >> fchar;

   cout << "Filled, hollow, mix, or random? [f/h/m/r] ";
   char ifFilled; cin >> ifFilled;

   cout << "Enter size: "; int size; cin >> size;

   /*
   Figure *userBox = new Square(size, ifFilled == 'f'?
               static_cast<FullyFilled *>(new Filled(fchar)):
               static_cast<FullyFilled *>(new Hollow(fchar))
               );
   */

   /*
   Figure *userBox = new Square(size,
                      ifFilled == 'f'?
                                new Filled(fchar):
                                new Hollow(fchar)
               );

   */
   Figure* userBox;
   if (ifFilled == 'f') {
      userBox = new Square(size, new Filled(fchar));
   } else if (ifFilled == 'h') {
      userBox = new Square(size, new Hollow(bchar));
   } else if (ifFilled == 'm') {
      userBox = new Square(size, new FullyFilled(bchar, fchar));
   } else if (ifFilled == 'r') {
      userBox = new Square(size, new RandomFilled(bchar, fchar));
   } else {
      cout << endl << "Invalid input" << endl;
      return 1;
   }

   cout << endl;
   userBox -> draw();
   cout << endl;
}
