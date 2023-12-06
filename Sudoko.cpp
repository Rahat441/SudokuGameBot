
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <math.h>
#include <iostream>
#include <unordered_set>
#include <set>
using namespace std;



class Sudoko{
    public:
        vector<int> tiles;
       
       char Board[9][9];

        Sudoko(int difficulty) {


            std::srand(static_cast<unsigned>(std::time(nullptr)));
            for (int i = 0; i < 9; ++i)
                for (int j = 0; j < 9; ++j)
                    Board[i][j] = '.';

            for (int i = 0; i < 9; ++i){
                for (int j = 0; j < 9; ++j){
                    vector<char> validMoves = Options(findQuad(i,j),i,j);
                    int randomNumber = std::rand() % validMoves.size() + 1;
                    int Decision  = std::rand() % (6 + difficulty) + 1 ;
                    if(Decision == 1){
                        
                        char a = randomNumber + '0';
                        Board[i][j] = a;
                    }
                }
            }
                    
                    
                        
        }

        bool isValidMove(int row, int col, int num) const {
            for (int i = 0; i < 9; ++i)
                if (Board[row][i] == num + '0' || Board[i][col] == num + '0')
                    return false;

            int startRow = 3 * (row / 3);
            int startCol = 3 * (col / 3);

            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    if (Board[startRow + i][startCol + j] == num + '0')
                        return false;

            return true;
        }
       
       
        // Display Functions 
        void DisplayOptions(int row, int col, size_t choice, vector<char> &moves){ // Displays options available for Cell
            cout<<"Selected CEll: "<<row<<col<<endl<<" Options For Cell: {";  
                for (auto t : moves) cout<<"[ "<<t<<" ],";
                cout<<"}"<<endl;
        }
        void printBoard() {
        for (int i = 0; i < 9; i++) {cout<<endl;
            for (int j = 0; j < 9; j++) {
                if(j ==3|| j==6 || j==9){cout<<"|";}
            cout<<"  "<<Board[i][j]<<"  ";
            }
            cout<< endl;
            if(i == 2 || i == 5){cout<<"_________________________________________________"; cout<<endl;}
        
        }cout<<endl;
    }

        //Helpers
        bool BoardFilled(){
            for(int i = 0; i < 9;i++)       //Is Board fULL
                for (int j = 0; j < 9; j++)
                if(Board[i][j] == '.')   return false;
            return isValidSudoku();       
        }
      //Helper itrs the board and calls solveSudoku when empty cell found
        void HelperSudoku(){  
            int i = 0;
            while(BoardFilled() != true ){
                for(int j = 0; j < 9; j++)
                    if(Board[i][j] == '.'){solveSudoku(i, j, 0);}  //Empty Cell Found    
                i++;if(i>8){i = 0;}
            }
        }
        // Function to initialize a Sudoku board with random values
        void solveSudoku(int row, int col, size_t choice){
        vector<char> movesAv = Options(findQuad(row,col),row,col);  //Find All options For chosen cell
      
        if(movesAv.size() > choice)     
        {   //if there are moves available for the selected Cell
                // after making a move update Tiles with Data For Past Cells played
            Board[row][col] = movesAv[choice];   
            tiles.push_back(row);tiles.push_back(col);tiles.push_back(choice);  
            return ;    
        }
        else{   
        // No Moves available to make, Backtrack to an prev move and select next option 
        //Backlog keeps log of the prev moves that have to be modified  

            vector<int> backLog; backLog.push_back(row);backLog.push_back(col);backLog.push_back(choice);
            int x = tiles[tiles.size()-3]; int y = tiles[tiles.size()-2]; int c = tiles[tiles.size()-1];
            Board[x][y] = '.';
            tiles.pop_back();tiles.pop_back();tiles.pop_back();
            solveSudoku(x,y,c+1);
            // Filling the cells Change
            for(auto x =0;x < backLog.size();x+=3){
                //Fills the cells that were erased 
                solveSudoku(backLog[x],backLog[x+1],0);
            } 
        }     
    }
  

    
    private:
        
        
    // The Sudoko Validator-> Checks If Board is Valid At current / final state 
        bool blockValid(int quad){
            int row, col;
            switch (quad) {
                    case 1:
                        row = 0; col = 0; break;
                    case 2:
                        row = 3; col = 0; break;
                    case 3:
                        row = 6; col = 0; break;
                    case 4:             //SECOND 
                        row = 0; col = 3; break;
                    case 5:
                        row = 3; col = 3; break;
                    case 6:
                        row = 6; col = 3; break;
                    case 7:             //THIRD 
                        row = 0; col = 6; break;
                    case 8:
                        row = 3; col = 6; break;
                    case 9:
                        row = 6; col = 6; break;    
                    default:
                    std::cout << "Invalid choice." << std::endl;break;
                }
            std::unordered_set<char> mySet ;
            // Check if element in the 3x3 box exists exists in the set 
            for(int i = row; i < 3 + row; i++){
                for(int j = col; j < 3 + col; j++){
                    if(Board[i][j] != '.'){
                        int searchElement = Board[i][j];
                        auto it = mySet.find(searchElement);
                        if (it == mySet.end()) {    // not found
                            mySet.insert(searchElement);
                        }
                        else{ return false;}
                    }
                }
                
            }
        return true;
        }
        bool isValidSudoku() {  //  Driver Tested&True 
            // 3x3 box check
            for(int i = 1; i <10; i++){
                if(blockValid(i) == false) return false;
            }
            //Horizontal 
            std::unordered_set<char> mySet ;
            for(int x = 0; x < 9; x++){
                for(int i = 0; i < 9 ; i++){
                    if(Board[x][i] != '.'){
                    int searchElement = Board[x][i];
                        auto it = mySet.find(searchElement);
                        if (it == mySet.end()) {  mySet.insert(searchElement);}
                        else{ cout<<x<<i;return false;} 
                    }
                }
                mySet.clear();
            }
        
            //Verical Check
            for(int x = 0; x < 9; x++){
                for(int i = 0; i < 9 ; i++){
                    if(Board[i][x] != '.'){
                    int searchElement = Board[i][x];
                        auto it = mySet.find(searchElement);
                        if (it == mySet.end()) {  mySet.insert(searchElement);}
                        else{ return false;} 
                    }
                }
                mySet.clear();
            }
        
          
        return true;
        }
    //Move Generator
        vector<char> Options(int quad, int xCor, int yCor){   
        // Looks For available moves for selected Cell considers whole board                                     
            vector<char> option;
            std::set<char> mySet;

            for(int i = 1; i <10;i++){char a = '0'+ i;mySet.insert(a);}
        //Selecting row col for quad of coice    
            int row=0;int col=0;
            switch (quad) {
                    case 1:
                        row = 0; col = 0; break;
                    case 2:
                        row = 3; col = 0; break;
                    case 3:
                        row = 6; col = 0; break;
                    case 4:             //SECOND 
                        row = 0; col = 3; break;
                    case 5:
                        row = 3; col = 3; break;
                    case 6:
                        row = 6; col = 3; break;
                    case 7:             //THIRD 
                        row = 0; col = 6; break;
                    case 8:
                        row = 3; col = 6; break;
                    case 9:
                        row = 6; col = 6; break;    
                    default:
                    std::cout << "Invalid choice." << std::endl;break;
                }
                
                // Check to find options in the quad 
                for(int i = row; i < 3 + row; i++){                
                        for(int j = col; j < 3 + col; j++){
                            if(Board[i][j] != '.') {
                                char searchElement = Board[i][j];
                                const auto it = mySet.find(searchElement);
                                if (it != mySet.end()) {    //  found
                                    mySet.erase(it);
                                }
                            }
                        }                
                    }
                

                
                //check to find horizontal options 
                for(int x = 0; x < 9; x++){
                    if(Board[xCor][x] != '.'){
                    char searchElement = Board[xCor][x];
                        auto it = mySet.find(searchElement);
                        if (it != mySet.end()) {  mySet.erase(it);}    
                    }
                }
                //Check Vertical 
                for(int x = 0; x < 9; x++){
                    char searchElement = Board[x][yCor];
                        auto it = mySet.find(searchElement);
                        if (it != mySet.end()) {  mySet.erase(it);}    
                
                }

                //Making set array 
                for (auto it = mySet.begin(); it != mySet.end(); ++it) {
                    option.push_back(*it);
            }
                return option;
        }
        int findQuad(int xCor, int yCor){
        // Quad is used to assighn segmt while checking 3x3 Box    
            if(xCor<3){     //top third
                if(yCor < 3 ) return 1; // first quad
                else if(yCor>=3 && yCor < 6)return 4; //fourth quad 
                else if(yCor > 5)return 7; //seventh  quad 
                }

            else if(xCor>=3 && xCor < 6){       //middle
                if(yCor <3)return 2; 
                else if(yCor>=3 && yCor < 6)return 5; 
                else if(yCor > 5)return 8; 
            }
            else{       // last third
                if(yCor <3)return 3; 
                else if(yCor>=3 && yCor < 6)return 6; 
                else if(yCor > 5)return 9; 
            }
            return -1;
        }

        
};

//  Game Driver 
int main() {
  
  Sudoko game(3); // set Difficulty 1 = easy - 3 = Hard
  cout<<"<<------Board generated for the game-------->> "<<endl;game.printBoard();
  
  game.HelperSudoku();
  game.printBoard();
    return 0;
}

