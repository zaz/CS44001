//
// Games, Template Method example
//
// Mikhail Nesterenko
// Modified by Zaz Brown
//

#include <ctime>
#include <cstdlib>
#include <iostream>

using std::cout; using std::endl;

// template for any game where players take
// turns to make moves
// and there is a winner
class Game{
public:
   Game():playersCount_(0), movesCount_(0), playerWon_(noWinner){}

   // template method
   void playGame(const int playersCount = 0) {
      playersCount_ = playersCount;
      movesCount_=0;

      initializeGame();

      for(int i=0; !endOfGame(); i = (i+1) % playersCount_ ){
         makeMove(i);
         if (i==playersCount_-1)
            ++movesCount_;
      }
      printWinner();
   }

   virtual ~Game(){}

protected:
   // primitive operations
   virtual void initializeGame() = 0;
   virtual void makeMove(int player) = 0;
   virtual void printWinner() = 0;
   virtual bool endOfGame() { return playerWon_ != noWinner;} // this is a hook
                   // returns true if winner is decided
   static const int noWinner=-1;

   int playersCount_;
   int movesCount_;
   int playerWon_;
};

// Monopoly - a concrete game implementing primitive
// operations for the template method
class Monopoly: public Game {
public:
   // implementing concrete methods
   void initializeGame(){
      playersCount_ = rand() % numPlayers_ + 1 ; // initialize players
   }

   void makeMove(int player) {
      if (movesCount_ > minMoves_){
         const int chance = minMoves_ + rand() % (maxMoves_ - minMoves_);
         if (chance < movesCount_) playerWon_= player;
      }
   }

   void printWinner(){
      cout << "Monopoly, player "<< playerWon_<< " won in "
           << movesCount_<< " moves." << endl;
   }

private:
   static const int numPlayers_ = 8; // max number of players
   static const int minMoves_ = 20; // nobody wins before minMoves_
   static const int maxMoves_ = 200; // somebody wins before maxMoves_
};

// Chess - another game implementing
// primitive operations
class Chess: public Game {
public:
   void initializeGame(){
      playersCount_ = numPlayers_; // initalize players
      for(int i=0; i < numPlayers_; ++i)
         experience_[i] = rand() % maxExperience_ + 1 ;
   }

   void makeMove(int player){
      if (movesCount_ > minMoves_){
         const int chance = (rand() % maxMoves_) / experience_[player];
         if (chance < movesCount_) playerWon_= player;
      }
   }

   void printWinner(){
      cout << "Chess, player " << playerWon_
           << " with experience " << experience_[playerWon_]
           << " won in "<< movesCount_ << " moves over"
           << " player with experience " << experience_[playerWon_== 0 ? 1:0]
           << endl;
   }

private:
   static const int numPlayers_ = 2;
   static const int minMoves_ = 2; // nobody wins before minMoves_
   static const int maxMoves_ = 100; // somebody wins before maxMoves_
   static const int maxExperience_ = 5; // player's experience
                              // the higher, the greater probability of winning
   int experience_[numPlayers_];
};

// YAGIPO - yet another game implementing primitive operations
// a.k.a. Dice
class Dice: public Game {
public:
   void initializeGame(){
      playersCount_ = numPlayers_;  // initalize players
      std::cout << "\nPlaying Dice:\n" << std::flush;
   }

   std::string name(int player) {
      return player == 0 ? "The computer" : "You";
   }

   void makeMove(int player){
      if (maxMoves_ <= movesCount_) {
         playerWon_= scores_[0] >= scores_[1] ? 0 : 1;
         return;
      }

      if (rollDiceP(player)) {
         scores_[player] = 5 + (rand() % 6) + (rand() % 6) + (rand() % 6)
                             + (rand() % 6) + (rand() % 6);
         std::cout << name(player) << " rolled " << scores_[player] << std::endl;
         passed_ = false;
      } else {
         std::cout << name(player) << " did not roll." << std::endl;
         if (passed_)
            playerWon_= scores_[0] >= scores_[1] ? 0 : 1;
         passed_ = true;
      }
      if (player == playersCount_ - 1)
         std::cout << std::endl;
   }

   // rollDice predicate: returns whether the player will roll the dice
   bool rollDiceP(int player) {
      // if it is the first round, roll the dice
      if (movesCount_ == 0) return true;

      // if the player is the computer, decide randomly
      if (player == 0) return rand() % 2;

      // if the player is human, prompt for input
      std::cout << "Roll again? [y/N] ";
      char input;
      std::cin >> input;
      return input == 'y' || input == 'Y';
   }

   void printWinner() {
      cout << name(playerWon_) << " won." << endl;
   }
private:
   static const int numPlayers_ = 2;
   static const int maxMoves_ = 3;
   int scores_[numPlayers_];
   bool passed_ = false;
};

int main() {
   srand(time(nullptr));

   Game* gp = nullptr;

   // play chess 8 times
   for (int i = 0; i < 8; ++i){
      gp = new Chess;
      gp->playGame();
      delete gp;
   }


   // play monopoly 8 times
   for (int i = 0; i < 8; ++i){
      gp = new Monopoly;
      gp->playGame();
      delete gp;
   }

   gp = new Dice;
   gp->playGame();
   delete gp;
}
