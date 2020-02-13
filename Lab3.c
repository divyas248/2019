#include <stdio.h>
#include <math.h>


int main(void)
{
	// Initiating and casting the variables
    double cost = 0;
    const double COUPONRATE = 0;
    double money = 0;
    int coffee = 0;
    int freeCoffee = 0;
    int coupons = 0;
    double moneyRemaining = 0;
    double averageSpending = 0;
    
	//Asking the user for the coffee cost and determining if it is a valid input
	printf ("How much does a coffee cost?\n");
    scanf("%lf", &cost);
    
    if (cost<0.01){
        printf("Invalid Input.\n");
        return 0;
    }
    
    //Determining the coupon rate and if it is valid input
    printf("How many coupons does it take to get a free coffee?\n");
    scanf ("%lf",&COUPONRATE);
    
    if (COUPONRATE<0 || COUPONRATE != (int) COUPONRATE){
        printf("Invalid Input.\n");
        return 0;
    }
    
    //Determining the user's input and decide if it is a valid input
    printf ("How much money do you have to spend on coffee this month?\n");
    scanf ("%lf", &money);
    
    if (money<0){
        printf("Invalid Input.\n");
        return 0 ;
    }

    //Calculating the number of coffees, free coffees, coupons, average spending and money remaining
    coffee = money/cost;
    coupons = coffee;
    while (coupons>=COUPONRATE){
        coupons = coupons - COUPONRATE;
        freeCoffee = freeCoffee + 1;
        coupons = coupons + 1;
    }
	
    moneyRemaining = money - (cost*coffee);
    averageSpending = (money-moneyRemaining)/(freeCoffee+coffee);
    
	//Determining the style of the output depending on the number of free coffees the user receives
    printf("This month, you can purchase %d coffees at $%.2lf each.\n", coffee, cost);
    
    if (freeCoffee>0){
        printf("You will be able to redeem an additional %d coffee(s) from coupons.\n", freeCoffee);
    }
    else{
        printf ("You will not be able to redeem any additional coffees from coupons this month.\n");
    }
    
	printf("At the end of the month, you will have $%.2lf and %d coupon(s) remaining.\n", moneyRemaining, coupons);
	printf("On average, you spent $%.2lf on each cup of coffee this month.\n", averageSpending);


    return 0;
    
        
    
    
    
    
    
    
    
}
    
	
