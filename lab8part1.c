#include <stdio.h>
#include <stdbool.h>

void printBoard (char board[][26], int n){
    // First line print (letters
    int i = 0;
    printf ("  ");
    for (i=97;i<n+97;i++){
        printf("%c", i);
    }
    printf ("\n");

    //Prints each row with the preceeding letter
    int j = 0;
    for (i=0; i<n;i++){
        printf("%c ", i+97);
        for(j=0;j<n;j++){
            printf("%c", board [i][j]);
        }
        printf("\n");
    }
}


//Checking if the position entered is valid and within the bounds
bool positionInBounds (int n, int row, int col){
    if (row>=0&&row<n){
        if(col>=0&&col<n){
            return true;
        }
    }
    return false;
}

bool checkLegalInDirection (char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol){
    int tempRow = row + deltaRow;
    int tempCol = col + deltaCol;
    int count =0;
    
    //Checks if the surrounding tile is empty or occupied by a colour
    while (tempRow >=0 && tempCol >=0 && tempCol<n && tempRow <n){
        if (board [tempRow][tempCol] != 'U' && board [tempRow][tempCol] != colour){
            count ++;
            tempRow = tempRow + deltaRow;
            tempCol = tempCol + deltaCol;
        } else if(count>0 && board [tempRow][tempCol] == colour){
            return true;
        } else{
            return false;
        }
    }
    return false;
}

bool checkDirections(int n, int i, int j, char board [][26], char colour, int aim, int *score){
    int deltaRow = -1, deltaCol =-1;
    bool state = false;
    int k=0;
    int l=0;
    *score = 0;
    
    int tempR =0, tempC =0;
    
    for(deltaRow = -1; deltaRow<=1;deltaRow++){
        for(deltaCol=-1; deltaCol<=1;deltaCol++){
            
            if (deltaRow + i >=0 && deltaRow<(n-1)){
                if(deltaCol + j >=0 && deltaCol<(n-1)){
                    if(deltaRow !=0 || deltaCol !=0){
                        state = checkLegalInDirection(board, n, i, j, colour, deltaRow, deltaCol);
                        tempR = deltaRow;
                        tempC = deltaCol;
                        k=0;
                        while(state&&positionInBounds (n, i+tempR,j+tempC)&&board [i+tempR][j+tempC]!=colour && board [i+tempR][j+tempC] !='U'){
                            k++;
                            tempR = tempR + deltaRow;
                            tempC = tempC + deltaCol;
                        }
                        if (aim==0 && state){
                            return true;
                        }
                        else if (state){
                            *score = *score +1;
                        }
                        if(state && aim==3){
                            for(l=0; l<=k;l++){
                                board[i+l*deltaRow][j+l*deltaCol]=colour;
                            }
                        }
                    }
                }
            }
        }
    }
    
    if (*score>0){
        return true;
    }else{
        return false;
    }
}


void flipFinder (int dimension, char position [][26], int *pRow, int *pCol, int aim, int *score, char player){
    int temp = 0;
    int i= 0;
    int j =0;
    bool state = false;
    *score = 0;
    for (i=0; i<dimension;i++){
                    for(j=0;j<dimension;j++){
                        if (position[i][j] != 'W' && position[i][j] != 'B'){
                            temp = 0;
                            state = checkDirections (dimension, i, j, position, player, aim, &temp);
                            if(state==true && temp>*score){
                                *pRow = i;
                                *pCol = j;
                                *score =temp;
                            }
                        }
                    }
                }
}


int main(void){
    //Declares and sets the Initial Values 
    int startPosition1 = 0;
    int startPosition2 = 0;
    int dimension = 0;
    int initial1 = 0;
    int initial2 = 0;
    char input1 = 'N';
    char input2 = 'N';
    char computer = 'N';
    char human = 'N';
    bool gameState = true;
    int i = 0;
    int j = 0;
    int pRowP = 0; 
    int pRowO =0;
    int pColP = 0;
    int pColO = 0;
    
    char player, oppose;
    int score = 0;
    int numPlayer = 0;
    bool state;
    int counterB= 0 ;
    int counterW = 0;
    int temporary = 0;
    
    //Declaring the 2-D Array
    printf("Enter the board dimension: ");
    scanf ("%d", &dimension);
    
    printf("Computer plays (B/W): ");
    scanf(" %c", &computer);
    if (computer == 'B'){   
        human = 'W';
    } else{
        human = 'B';
    }
        
    static char position [26][26];
    
    //Setting up the Board 
    for (initial1 = 0; initial1<dimension; initial1++){
        for (initial2=0; initial2<dimension; initial2++){
            position [initial1][initial2] = 'U';
        }
    }
    
    
    //Putting the initial positions for W and B player in the beginning
    startPosition1 = dimension/2 - 1;
    startPosition2 = (dimension/2);
    position [startPosition1][startPosition1]  = 'W';
    position [startPosition1][startPosition2]  = 'B';
    position [startPosition2][startPosition1]  = 'B';
    position [startPosition2][startPosition2]  = 'W';
    
    if (human == 'B'){
        numPlayer = 1;
    } else{
        numPlayer =0;
    }
    
    //Starts with player 1 if not it is the computer's turn
    player = 'B';
    oppose = 'W';
    printBoard (position, dimension);
    int scoreP = 0;
    int scoreO = 0;
    while (gameState){
            flipFinder (dimension, position, &pRowP, &pColP, 1, &scoreP, player);
            flipFinder (dimension, position, &pRowO, &pColO, 1, &scoreO, oppose);            
        counterB = 0;
        counterW = 0;
        for (i=0;i<dimension;i++){
            for(j=0;j<dimension;j++){
                if (position[i][j] == 'B'){
                    counterB ++;
                }else if (position [i][j] == 'W'){
                    counterW ++;
                }
            }
        }
        
        if (counterB +counterW == (dimension*dimension) || (scoreP ==0 && scoreO ==0)){
            if (counterB>counterW){
                printf("B player wins.\n");
            } else if (counterW>counterB){
                printf("W player wins.\n");
            } else if (counterW==counterB){
                printf("Draw!\n");
            }
            gameState = false;
            return 0;
        }
        if(scoreP==0){
            printf("%c player has no valid move.\n", player);
        }
        
        if ((scoreP != 0 || scoreO !=0)&& scoreP != 0){
            if (numPlayer == 1){
                printf("Enter move for colour %c (RowCol): ", player);
                scanf (" %c%c", &input1, &input2);
    
                i = input1-97;
                j = input2-97;

                //Checks if it's within the bounds and identifies if valid
                bool inBounds = positionInBounds(dimension, i,j);
                if (inBounds ==false){
                    printf("Invalid move.\n");
                    printf("%c player wins.\n", oppose);
                    return 0;
                }
                state = checkDirections(dimension, i, j, position, player, 1, &temporary);
                if (state ==false){
                    printf("Invalid move.\n");
                    printf("%c player wins.\n", oppose);
                    return 0;
                }else{
                    gameState = checkDirections(dimension, i, j, position,player, 3, &score);
                    if (gameState){
                        position [i][j] = player;
                        printBoard(position, dimension);
                    }
                }
            }else if (numPlayer ==0) {
                if (scoreP != 0){
                    printf("Computer places %c at %c%c.\n",player, pRowP+97, pColP+97);
                    state = checkDirections(dimension, pRowP,pColP,position,player,3,&score);
                    printBoard(position,dimension);
                }
        }
        }
        
        
        if (numPlayer ==0){
            numPlayer =1;
        }else {
            numPlayer =0;
        }
        
        if (player == 'B'){
            player = 'W';
            oppose = 'B';
        } else {
            player = 'B';
            oppose = 'W';
        }
    }
    return 0;
}