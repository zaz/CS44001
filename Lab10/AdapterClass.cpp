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
   // it may make more sense to call these:
   LegacyRectangle(int topLeftX,       // left
                   int topLeftY,       // top
                   int bottomRightX,   // right
                   int bottomRightY):  // bottom
      topLeftX_(topLeftX),
      topLeftY_(topLeftY),
      bottomRightX_(bottomRightX),
      bottomRightY_(bottomRightY){}

   void oldDraw() const {
      for (int i=0; i < bottomRightY_; ++i) {
         for (int j=0; j < bottomRightX_; ++j)
            if (i >= topLeftY_ && j >= topLeftX_)
               cout << '*';
            else
               cout << ' ';
         cout << endl;
      }
   }

   void move(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) {
      topLeftX_ = topLeftX;
      topLeftY_ = topLeftY;
      bottomRightX_ = bottomRightX;
      bottomRightY_ = bottomRightY;
   }

  int getTopLeftX() const { return topLeftX_; }
  int getTopLeftY() const { return topLeftY_; }
  int getBottomRightX() const { return bottomRightX_; }
  int getBottomRightY() const { return bottomRightY_; }

   // defining top/left and bottom/right coordinates

// defining top/left and bottom/right coordinates
private:
   int topLeftX_;
   int topLeftY_;
   int bottomRightX_;
   int bottomRightY_;
};

// adapter uses multiple inheritance to inherit
// interface and implementation
class SquareAdapter: public Square,
                     private LegacyRectangle {
public:
   SquareAdapter(int size): LegacyRectangle(0,0,size,size){};
   int size() const { return getBottomRightX() - getTopLeftX(); };

   void draw() override {
      oldDraw();
   }
};


int main() {
   Square *square = new SquareAdapter(13);
   square->draw();
}
