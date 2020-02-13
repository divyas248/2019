#include <stdio.h>
#include <math.h>

int main(void)
{
	// This initializes and defines all the variables
	double purchasePrice=0;
	double interestRate = 0;
	int numberMonths=0;
	double monthlyPayment=0;
	double totalCost=0;
	
	//The following statements print the questions, and retrieve the user's information
	printf("Enter the purchase price of the item: ");
	scanf("%lf", &purchasePrice);
	
	printf("Enter the interest rate per year as a percentage: ");
	scanf("%lf", &interestRate);
	
	printf("Enter the number of months for repayment: ");
	scanf("%d",&numberMonths);
	
	//Converts the interest Rate to percent, then calculates the monthly payment and total cost
	interestRate = interestRate/(100*12);
	monthlyPayment= (interestRate/(1-pow(1+interestRate, -1*numberMonths)))*purchasePrice;
	totalCost = monthlyPayment * numberMonths;
	
	//Outputs the information that was caluculated to the user
	printf("The monthly payment is : %.2lf\n", monthlyPayment);
	printf ("The total cost of the purchase is: %.2lf\n", totalCost);
	return 0;
}