// figures: class adapter pattern
// Mikhail Nesterenko
// Modified by Zaz Brown

#include <iostream>

using std::cout; using std::endl;

// base interface
class Square {
public:
   virtual void draw()=0;
   virtual ~Square(){}
};

// adaptee/implementer
class LegacyRectangle {
public:
   LegacyRectangle(int left,     // topLeftX
                   int top,      // topLeftY
                   int right,    // bottomRightX
                   int bottom):  // bottomRightY
      left_(left),
      top_(top),
      right_(right),
      bottom_(bottom){}

   void oldDraw() const {
      for (int i=0; i < bottom_; ++i) {
         for (int j=0; j < right_; ++j)
            if (i >= top_ && j >= left_)
               cout << '*';
            else
               cout << ' ';
         cout << endl;
      }
   }

   void move(int left, int top, int right, int bottom) {
      left_ = left;
      top_ = top;
      right_ = right;
      bottom_ = bottom;
   }

   // x coordinates
   int getLeft() const { return left_; }
   int getRight() const { return right_; }
   // y coordinates
   int getTop() const { return top_; }
   int getBottom() const { return bottom_; }

   // defining top/left and bottom/right coordinates

// defining top/left and bottom/right coordinates
private:
   int left_;
   int top_;
   int right_;
   int bottom_;
};

// adapter uses multiple inheritance to inherit
// interface and implementation
class SquareAdapter: public Square,
                     private LegacyRectangle {
public:
   SquareAdapter(int size): LegacyRectangle(0,0,size,size){};
   int size() const { return getRight() - getLeft(); };
   void resize(int newSize) {
      const int left = getLeft();
      const int top = getLeft();
      move(left, top, left+newSize, top+newSize);
   }
   void draw() override {
      oldDraw();
   }
};


int main() {
   cout << "What size square would you like to draw? ";
   int size;
   std::cin >> size;

   SquareAdapter square(size);
   square.draw();

   cout << "What size would you like to redraw the sequare to? ";
   std::cin >> size;

   square.resize(size);
   square.draw();
}
