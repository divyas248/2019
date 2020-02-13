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

//This function checks if the direction will result in a legal move
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


//This checks all eight directions then calls the checkLegalInDirection. 
bool checkDirections(int n, int i, int j, char board [][26], char colour, int aim, int *score){
    int deltaRow = -1, deltaCol =-1;
    bool state = false;
    int k=0;
    int l=0;
    *score = 0;
    
    int tempR =0, tempC =0;
    
	//Uses nested for loops to check all directions
	//aim = 1 --> to check
	// aim = 3 --> to change the position
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
    
	//If it is valid position returns true otherwise it returns false
    if (*score>0){
        return true;
    }else{
        return false;
    }
}

//This is used to go through the entire array, and find the empty spaces then call other functions to check if it is a valid position
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
int compareC2 (int dimension, int i, int j, char board [][26], char player, char oppose){
	char tempBoard [26][26];
	int k = 0, l=0;
	int temp=0;
	bool state;
	int score = 0;
	
	for (k=0;k<dimension;k++){
		for (l=0;l<dimension;l++){
			tempBoard [k][l] = board [k][l];
		}
	}
	tempBoard [i][j] = oppose;
	 score = 0;
                int pRow = 0, pCol =0;
                for (k=0; k<dimension;k++){
                    for(l=0;l<dimension;l++){
                        if (tempBoard[k][l] != 'W' && tempBoard[k][l] != 'B'){
                            temp = 0;
                            state = checkDirections (dimension, k, l, tempBoard, oppose, 1, &temp);
                            
                            
                            if(state && temp>score){
                                pRow = i;
                                pCol = j;
                                score = temp;
                            }
                            
                        }
                    }
                }
                return score;
}

int compareC (int dimension, int i, int j, char board [][26], char player, char oppose){
	char tempBoard [26][26];
	int k = 0, l=0;
	int score ;
	int temp=0;
	bool state;
	
	
	for (k=0;k<dimension;k++){
		for (l=0;l<dimension;l++){
			tempBoard [k][l] = board [k][l];
		}
	}
	tempBoard [i][j] = player;
	 score = 0;
                int pRow = 0, pCol =0;
                for (k=0; k<dimension;k++){
                    for(l=0;l<dimension;l++){
                        if (tempBoard[k][l] != 'W' && tempBoard[k][l] != 'B'){
                            temp = 0;
                            state = checkDirections (dimension, k, l, tempBoard, oppose, 1, &temp);
                            
                            if(state){
                                temp = compareC2(dimension, i, j, tempBoard,player, oppose)- temp;
                            }
                            
                            if(state && temp>score){
                                pRow = i;
                                pCol = j;
                                score = temp;
                            } 
                            
                        }
                    }
                }
                return score;
}
void flipFinderC (int dimension, char position [][26], int *pRow, int *pCol, char player, char oppose){
    int temp = 0;
    int i= 0;
    int j =0;
	int temp1= 0;
    bool state = false;
    int score = 0;
    int score1 = 0;
    for (i=0; i<dimension;i++){
                    for(j=0;j<dimension;j++){
                        if (position[i][j] != 'W' && position[i][j] != 'B'){
                            state = checkDirections (dimension, i, j, position, player, 1, &temp);
							
							if (state && temp==score){
								temp1 = temp + compareC(dimension,i, j, position, player, oppose);
                                if (temp1>score1){
                                    score1 = temp1;
                                    *pRow = i;
                                    *pCol = j;
                                }
							}
                            if(state==true && temp>score){
                                *pRow = i;
                                *pCol = j;
                                score = temp;
                                
                            }
                        }
                    }
                }
}
int compareC31 (int dimension, int i, int j, char board [][26], char player, char oppose){
	char tempBoard [26][26];
	int k = 0, l=0;
	int score ;
	int temp=0;
	bool state;
	
	
	for (k=0;k<dimension;k++){
		for (l=0;l<dimension;l++){
			tempBoard [k][l] = board [k][l];
		}
	}
	tempBoard [i][j] = player;
	 score = 0;
                int pRow = 0, pCol =0;
                for (k=0; k<dimension;k++){
                    for(l=0;l<dimension;l++){
                        if (tempBoard[k][l] != 'W' && tempBoard[k][l] != 'B'){
                            temp = 0;
                            state = checkDirections (dimension, k, l, tempBoard, oppose, 1, &temp);
                            
                            //temp is the value of future player moves minus current 
                            if(state && temp>score){
                                pRow = i;
                                pCol = j;
                                score = temp;
                            } 
                            
                        }
                    }
                }
                return score;
}

int compareC21 (int dimension, int i, int j, char board [][26], char player, char oppose){
	char tempBoard [26][26];
	int k = 0, l=0;
	int temp=0;
	bool state;
	int score = 0;
	
	for (k=0;k<dimension;k++){
		for (l=0;l<dimension;l++){
			tempBoard [k][l] = board [k][l];
		}
	}
	tempBoard [i][j] = oppose;
	 score = 0;
                int pRow = 0, pCol =0;
                for (k=0; k<dimension;k++){
                    for(l=0;l<dimension;l++){
                        if (tempBoard[k][l] != 'W' && tempBoard[k][l] != 'B'){
                            temp = 0;
                            state = checkDirections (dimension, k, l, tempBoard, player, 1, &temp);
                            
                            //temp is the value of future player moves minus current 
                            if(state){
                                temp = temp - compareC31(dimension, k, l, tempBoard,player, oppose);
                            }
                            
                            if(state && temp>score){
                                pRow = i;
                                pCol = j;
                                score = temp;
                            } 
                            
                        }
                    }
                }
                return score;
}

int compareC1 (int dimension, int i, int j, char board [][26], char player, char oppose){
	char tempBoard [26][26];
	int k = 0, l=0;
	int score ;
	int temp=0;
	bool state;	
	
	for (k=0;k<dimension;k++){
		for (l=0;l<dimension;l++){
			tempBoard [k][l] = board [k][l];
		}
	}
	tempBoard [i][j] = player;
	 score = 0;
                int pRow = 0, pCol =0;
                for (k=0; k<dimension;k++){
                    for(l=0;l<dimension;l++){
                        if (tempBoard[k][l] != 'W' && tempBoard[k][l] != 'B'){
                            temp = 0;
                            state = checkDirections (dimension, k, l, tempBoard, oppose, 1, &temp);
                            
                            //temp is the value of future player moves minus current 
                            if(state){
                                temp = compareC21(dimension, k, l, tempBoard,player, oppose)- temp;
                            }
                            
                            if(state && temp>score){
                                pRow = i;
                                pCol = j;
                                score = temp;
                            } 
                            
                        }
                    }
                }
                return score;
}
void flipFinderC1 (int dimension, char position [][26], int *pRow, int *pCol, char player, char oppose){
    int temp = 0;
    int i= 0;
    int j =0;
	int temp1= 0;
    bool state = false;
    int score = 0;
    int score1 = 0;
    for (i=0; i<dimension;i++){
                    for(j=0;j<dimension;j++){
                        if (position[i][j] != 'W' && position[i][j] != 'B'){
                            state = checkDirections (dimension, i, j, position, player, 1, &temp);
							//temp number of flips for player
							if (state && temp==score){
								temp1 = temp + compareC1(dimension,i, j, position, player, oppose);
                                if (temp1>score1){
                                    score1 = temp1;
                                    *pRow = i;
                                    *pCol = j;
                                }
							}
                            if(state==true && temp>score){
                                *pRow = i;
                                *pCol = j;
                                score = temp;
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
    int turn = 0;
    int secondTheorem = false;
    int row = 0;
    int col = 0;
    
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
		turn ++;
		//Find if there are valid moves for player and opponent
		flipFinder (dimension, position, &pRowP, &pColP, 1, &scoreP, player);
		flipFinder (dimension, position, &pRowO, &pColO, 1, &scoreO, oppose); 

		//Count the number of black and white tiles
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
        
		//Using if statements to determine draws, wins, and losses and exiting the program
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
		
		//Prints if the player does not have any valid moves
        if(scoreP==0){
            printf("%c player has no valid move.\n", player);
        }
        
		//This if statement to identify if the round qualifies for further steps
        if ((scoreP != 0 || scoreO !=0)&& scoreP != 0){
            //Runs if it is the human's turn and gets the input 
			if (numPlayer == 1){
                printf("Enter move for colour %c (RowCol): ", player);
                scanf (" %c%c", &input1, &input2);
    
                i = input1-97;
                j = input2-97;


                if (turn ==2 && i==2 && j ==4){
                    secondTheorem = true;
                }

                //Checks if it's within the bounds and identifies if valid
                bool inBounds = positionInBounds(dimension, i,j);
                if (inBounds ==false){
                    printf("Invalid move.\n");
                    printf("%c player wins.\n", oppose);
                    return 0;
                }
				
				//Check if a valid position and if so it changes the board accordingly
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
				
			//For the computer's turn	
            }else if (numPlayer ==0) {
                if(secondTheorem == false){
                if (player == 'W'){
                    flipFinderC(dimension, position, &pRowP, &pColP, player, oppose);
                    printf("Computer places %c at %c%c.\n",player, pRowP+97, pColP+97);
                    state = checkDirections(dimension, pRowP,pColP,position,player,3,&score);
                    printBoard(position,dimension);
                }
                else if(player == 'B'){
                    flipFinderC(dimension, position, &pRowP,&pColP, player, oppose);
                    printf("Computer places %c at %c%c.\n",player, pRowP+97, pColP+97);
                    state = checkDirections(dimension, pRowP,pColP,position,player,3,&score);
                    printBoard(position,dimension);
                }
                }
                
                if(secondTheorem == true){
                    if (player == 'W'){
                    flipFinderC1(dimension, position, &pRowP, &pColP, player, oppose);
                    printf("Computer places %c at %c%c.\n",player, pRowP+97, pColP+97);
                    state = checkDirections(dimension, pRowP,pColP,position,player,3,&score);
                    printBoard(position,dimension);
                }
                else if(player == 'B'){
                    flipFinderC1(dimension, position, &pRowP,&pColP, player, oppose);
                    printf("Computer places %c at %c%c.\n",player, pRowP+97, pColP+97);
                    state = checkDirections(dimension, pRowP,pColP,position,player,3,&score);
                    printBoard(position,dimension);
                }
                }
        }
        }
        
        //Changes the player number and character after each turn 
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
