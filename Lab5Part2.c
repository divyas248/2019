#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//This function generates random numbers between 1 and 6, inclusive and finds their sum
int rollDice (void){
    int randomNumber = 0 ;
    int randomNumber2 = 0;
    int sum=0;
    randomNumber = rand()%6 + 1;
    randomNumber2 = rand()%6 + 1;
    sum = randomNumber + randomNumber2;
    return sum;
}

//This function returns true or false, by using the game rules to identify if the sum results in a win or loss
bool playGame(void){
    int sum = 0;
    int sum2 = 0;
    sum = rollDice();
    printf("You rolled: %d\n", sum);
    
	//Checks the initial sum and checks if it qualifies for an immediate win or loss
    if (sum==7 || sum ==11){
        printf("You win!\n");
        return true;
    }
    else if (sum == 2 || sum ==3 || sum ==12){
        printf("You lose!\n");
        return false;
    }
	
	//If it is neither win or lose, it sets a point and circulates until it loses or wins
    else{
        printf ("Your point is: %d\n", sum);
        while (sum2!=7 && sum2!=sum){
            sum2 = rollDice();
            printf("You rolled: %d\n", sum2);
        } 
        if (sum2 ==7){
            printf("You lose!\n");
            return false;
        }
        if (sum2==sum){
            printf("You win!\n");
            return true;
        }
    }
	return false;
}

	//Keeps count of the total wins and losses
    void winLoss(void){
        bool result = false;
        bool playAgain = true;
        char answer;
        int win = 0;
        int loss = 0;
        
        
		//Asks the user if they want to play again and if not displays the wins and losses
        do {
        result  = playGame();
        printf("Play again? ");
        scanf (" %c", &answer);
        if (result == true){
            win++;
        }
        
        if (result == false){
            loss++;
        }
        
		//Evaluates the character that the user enters
        if (answer == 'y' || answer == 'Y'){
            playAgain = true;
        }else if (answer!='y' || answer!='Y'){
                playAgain = false;
        }
        }while (playAgain ==true);      
  
		//Prints the win and loss count
        printf ("\nWins: %d\n", win);
        printf("Losses: %d\n", loss);
    }

    
