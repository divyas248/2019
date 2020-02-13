#include <stdio.h>
#include <stdbool.h>

void printBoard (char board[][26], int n){
    // First line print letters
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

//This checks the colours that can be found in the specified line, and checks if its a valid position
bool checkLegalInDirection (char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol){
    int tempRow = row + deltaRow;
    int tempCol = col + deltaCol;
    bool state = false;
    int count =0;
    
    //Checks if the tile is empty or occupied by a colour as you travel along the line
    while (tempRow >=0 && tempCol >=0 && tempCol<n && tempRow <n && state ==false){
		//If the tile is empty and does not equal colour then increase count
        if (board [tempRow][tempCol] != 'U' && board [tempRow][tempCol] != colour){
            state =false;
            count ++;
            tempRow = tempRow + deltaRow;
            tempCol = tempCol + deltaCol;
        } 
		//If the tile is the colour and count is greater than 0, then legal move
		else if(count>0 && board [tempRow][tempCol] == colour){
            state =true;
            return true;
        } else{
            return false;
        }
    }
    return false;
    

}

//Checks all eight directions
bool checkDirections1 (int n, int i, int j, char board [][26], char colour, int aim){
    int deltaRow = 100;
    int deltaCol = 100;
    bool currentState = false ;
    
                //Checks bottom row left column
                if (i>0 && j>0){
                    deltaRow = -1;
                    deltaCol = -1;
                    currentState = checkLegalInDirection (board, n, i, j, colour, deltaRow, deltaCol );
                }
                
				//check the middle row left column
                if (currentState == false && j>0){
                    deltaCol = -1;
                    deltaRow = 0;
                    currentState = checkLegalInDirection (board, n, i, j, colour, deltaRow, deltaCol );
                    
                }
				
				//Checks top row left column
                if (currentState == false && j>0 && i<n-1){
                    deltaCol = -1;
                    deltaRow = 1;
                    currentState = checkLegalInDirection (board, n, i, j, colour, deltaRow, deltaCol );
                }
                
				//Check middle column bottom row
                if (currentState == false && i>0){
                    deltaCol = 0;
                    deltaRow = -1;
                    currentState = checkLegalInDirection (board, n, i, j, colour, deltaRow, deltaCol );
                }
                
				//Checks middle column top row
                if (currentState ==false && i<n-1){
                    deltaCol = 0;
                    deltaRow = 1;
                    currentState = checkLegalInDirection (board, n, i, j, colour, deltaRow, deltaCol );
                }
                
				//Checks bottom row right column
                if (currentState == false && i>0 && j<(n-1)){
                    deltaCol = 1;
                    deltaRow = -1;
                    currentState = checkLegalInDirection (board, n, i, j, colour, deltaRow, deltaCol );
                }
                
				//Checks middle row right column
                if (currentState == false && j<(n-1)){
                    deltaCol = 1;
                    deltaRow = 0;
                    currentState = checkLegalInDirection (board, n, i, j, colour, deltaRow, deltaCol );
                }
                
				//Checks top row right column
                if (currentState == false && i<(n-1) && j<(n-1)){
                    deltaCol = 1;
                    deltaRow = 1;
                    currentState = checkLegalInDirection (board, n, i, j, colour, deltaRow, deltaCol );
                }
                
				//If the move works then it changes the array accordingly
				//If aim =1, then the move is being made, if aim=0 its for the list of moves
                if (currentState == true && aim ==1){
                    board[i+deltaRow][j+deltaCol] = colour;
                    board [i][j] = colour;
                    return true;
                }
                else if (currentState == true){
                    return true;
                } else {
                    return false;
                }
}
bool checkDirections (int n, int i, int j, char board [][26], char colour, int aim){
    int deltaRow = 100;
    int deltaCol = 100;
    bool currentState = false ;
	int counter = 0;
    
                //Checks bottom row left column
                if (i>0 && j>0){
                    deltaRow = -1;
                    deltaCol = -1;
                    currentState = checkLegalInDirection (board, n, i, j, colour, deltaRow, deltaCol );
					if (currentState == true && aim ==1){
						board[i+deltaRow][j+deltaCol] = colour;
						board [i][j] = colour;
						counter ++;
					}else if (currentState == true){
						counter ++;
					}
                }
				
				currentState = false;
				//check the middle row left column
                if (j>0){
                    deltaCol = -1;
                    deltaRow = 0;
                    currentState = checkLegalInDirection (board, n, i, j, colour, deltaRow, deltaCol );
					if (currentState == true && aim ==1){
						board[i+deltaRow][j+deltaCol] = colour;
						board [i][j] = colour;
						counter ++;
					}else if (currentState == true){
						counter ++;
					}
                    
                }
				
				currentState = false;
				//Checks top row left column
                if (j>0 && i<n-1){
                    deltaCol = -1;
                    deltaRow = 1;
                    currentState = checkLegalInDirection (board, n, i, j, colour, deltaRow, deltaCol );
					if (currentState == true && aim ==1){
						board[i+deltaRow][j+deltaCol] = colour;
						board [i][j] = colour;
						counter ++;
					}else if (currentState == true){
						counter ++;
					}
                }
                
				currentState = false;
				//Check middle column bottom row
                if (i>0){
                    deltaCol = 0;
                    deltaRow = -1;
                    currentState = checkLegalInDirection (board, n, i, j, colour, deltaRow, deltaCol );
					if (currentState == true && aim ==1){
						board[i+deltaRow][j+deltaCol] = colour;
						board [i][j] = colour;
						counter ++;
					}else if (currentState == true){
						counter ++;
					}
                }
                
				currentState = false;
				//Checks middle column top row
                if (i<n-1){
                    deltaCol = 0;
                    deltaRow = 1;
                    currentState = checkLegalInDirection (board, n, i, j, colour, deltaRow, deltaCol );
					if (currentState == true && aim ==1){
						board[i+deltaRow][j+deltaCol] = colour;
						board [i][j] = colour;
						counter ++;
					}else if (currentState == true){
						counter ++;
					}
                }
                
				currentState = false;
				//Checks bottom row right column
                if (i>0 && j<(n-1)){
                    deltaCol = 1;
                    deltaRow = -1;
                    currentState = checkLegalInDirection (board, n, i, j, colour, deltaRow, deltaCol );
					if (currentState == true && aim ==1){
						board[i+deltaRow][j+deltaCol] = colour;
						board [i][j] = colour;
						counter ++;
					}else if (currentState == true){
						counter ++;
					}
                }
                
				currentState = false;
				//Checks middle row right column
                if (j<(n-1)){
                    deltaCol = 1;
                    deltaRow = 0;
                    currentState = checkLegalInDirection (board, n, i, j, colour, deltaRow, deltaCol );
					if (currentState == true && aim ==1){
						board[i+deltaRow][j+deltaCol] = colour;
						board [i][j] = colour;
						counter ++;
					} else if (currentState == true){
						counter ++;
					}
                }
                
				currentState = false;
				//Checks top row right column
                if (i<(n-1) && j<(n-1)){
                    deltaCol = 1;
                    deltaRow = 1;
                    currentState = checkLegalInDirection (board, n, i, j, colour, deltaRow, deltaCol );
					if (currentState == true && aim ==1){
						board[i+deltaRow][j+deltaCol] = colour;
						board [i][j] = colour;
						counter ++;
					}else if (currentState ==true){
						counter ++;
					}
                }
                
				//If the move works then it changes the array accordingly
				//If aim =1, then the move is being made, if aim=0 its for the list of moves
                
				if (counter>0){
                    return true;
                } else {
                    return false;
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
    char input3 = 'N';
    char colour = 'N';
    bool state = false;
    int aim =0;
    
    //Declaring the 2-D Array
    printf("Enter the board dimension: ");
    scanf ("%d", &dimension);
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
    
    printBoard(position,dimension);

    printf("Enter board configuration: \n");
    
    // Identifying the input of the user
    do{
        scanf(" %c%c%c", &input1, &input2, &input3);
        if (input1 != '!'&& input2 !='!'&& input3 !='!'){
			position[input2-97][input3-97] = input1;
        }
    } while (input1 != '!'&& input2 !='!'&& input3 !='!');
    
    //Prints the board 
    printBoard (position, dimension);
    printf ("Available moves for W:\n");
    colour = 'W';
    
    //Determines the possible moves for White
    int i =0, j=0;
    aim =0;
    for (i=0; i<dimension;i++){
        for(j=0;j<dimension;j++){
            if (position[i][j] != 'W' && position[i][j] != 'B'){
                state = checkDirections1 (dimension, i, j, position, colour, aim);
                if (state){
                    printf ("%c%c\n", i+97, j+97);
                }
            }
        }
    }
    
    //Determines the possible moves for B
    printf("Available moves for B:\n");
    colour = 'B';
    aim =0;
    for (i=0; i<dimension;i++){
        for(j=0;j<dimension;j++){
            if (position[i][j] != 'W' && position[i][j] != 'B'){
                state = checkDirections1 (dimension, i, j, position, colour, aim);
                if (state){
                    printf("%c%c\n", i+97, j+97);
                }
            }
        }
    }
    
    //Asks for  move
    printf("Enter a move: \n");
    scanf (" %c%c%c", &input1, &input2, &input3);
    
    colour = input1;
    i = input2-97;
    j = input3-97;

    //Checks if it's within the bounds and identifies if valid
    bool inBounds = false;
    inBounds = positionInBounds(dimension, i,j);
    
    
    //Invalid Move
    if (inBounds ==false){
        printf("Invalid move.\n");
        printBoard(position, dimension);
        return 0;
    } 
    
    //Changes the board according to the valid move or prints inlvalid move
    else{
        aim = 1;
        state = checkDirections(dimension, i, j, position,colour, aim);
        if (state){
            printf("Valid move.\n");
            position [i][j] = colour;
            printBoard(position, dimension);
        }else {
            printf ("Invalid move.\n");
            printBoard(position, dimension);
            }
    }
    return 0;
}