# ENGG 1410 Lab 2

### Problem Overview
Syntax, logic, and runtime errors exist in the example code, correct these. 
This problem should be <br> solved with no optimization, and correctly output the 13% tax added to an input. I used logical <br> analysis to solve the problem.
 
### Error Analysis
- (a) No syntax errors are present.
- (b) No semantic and logical errors are present.
- (c) None, it now solves the problem correctly
- (d) There were many errors in the initial program that was fixed
  - Syntax (missing ;)
  - Logical
    - int instead of a float for the input variable
    - Mixing up input and output messages
    - Not printing to correct decimal
    - Extra variables that were used instead of the correct variables.
  - Semantic
    - Using useless const char[] instead of passing directly to printf
    - Passing an int instead of float* to scanf

```c
#include <stdio.h>
#include <math.h>

int main(void){
    float taxPercent = 0.13; // what percent tax to use

    float amount = 0;

    printf("Enter an amount: ");
    scanf("%f", &amount);

    float taxAmount = amount * taxPercent;
    float totalAmount = amount + taxAmount;

    printf("With tax added: $%.2f\n", totalAmount);
}
```