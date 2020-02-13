#include <stdio.h>
#include <math.h>



//Inputs: 2 doubles
//Outputs: 3 doubles rounded to two decimal places.


int main(void)
{
    //The next three lines output the question and save the input as doubles
	printf("Enter two positive numbers: ");
    double number1 = 0, number2 = 0;
    scanf ("%lf %lf", &number1, &number2);
    
    //Functions: The next lines determine product, difference and sum of the roots
    double product = 0, difference = 0, SumOfRoots = 0;
    product =  number1*number2;
    difference = number1 - number2;
    SumOfRoots = sqrt(number1) + sqrt(number2);
    
    //Displaying the final message to the user with two decimal places
    printf ("The product is: %.2lf, the difference is: %.2lf and the sum of roots is: %.2lf\n", product, difference, SumOfRoots);

	return 0;
}



int main (void){
	int num1 = 0;
	int four = 0;
	input(&num1);
	four = add4(num1);
	four  = shift(four);
	printOutput(four, num1);
}