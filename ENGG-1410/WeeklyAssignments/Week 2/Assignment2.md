# ENGG 1410 Assignment 2

### Level 1

1. %
2. char (is a reserved word), 6_05 (starts with a number), A$ compiles but is a language extension. _1312 and _ compile but are reserved for the compiler.
3. Assuming we #include <stdio.h>
```
Testing .......1...2..3
```
4. (), ++, *, /, %, +, -, !=
5.  
```c
// Missing #include <stdio.h>

int main(Void) // Should be: int main(void)
{
    INT sum; // Should be: int sum;
    /* Comput ReZult // Should be: /* Compt Result */
    sum = 25 + 37 -19 // Should be sum = 25 + 37 -1;

    /* Display Results // // Should be: /* Display Results */
    printf("The answer is %i\n"        sum); // Should be: printf("The answer is %i \n", sum);

    return 0;
}
```
6. AND -> &&, OR -> ||, NOT -> !

AND
| A | B | R |
|---|---|---|
| 0 | 0 | 0 |
| 0 | 1 | 0 |
| 1 | 0 | 0 |
| 1 | 1 | 1 |

OR
| A | B | R |
|---|---|---|
| 0 | 0 | 0 |
| 0 | 1 | 1 |
| 1 | 0 | 1 |
| 1 | 1 | 1 |

NOT
| A | R |
|---|---|
| 0 | 1 |
| 1 | 0 |

1. The result is 95
2. x = 4.5, n = 4
3. * a) it prints the ascii value of c4
   * b) it prints the ascii character of i
    * c) to do float division
    * d) because the values correspond to different ascii values.
4.  * a) true
    * b) 17
    * c) 5.0
    * d) 5.75
5.  * a) 2.5
    * b) 10.0
    * c) 11.2


### 2 Tracing

12. x = 1.5, y = 1

12. 
```
i = 4
j = 9
k = 2 m = 9

i = 4
j = 9
k = 2 n = 10

i = 4
j = 9
k = 10

i = 4
j = 9
k = 10
```
14. it will print 15.0

### 3 Programming

15. 
```c
#include <stdio.h>

int main(void) {
    printf("Enter an amount:");
    float val;
    scanf("%f", &val);
    printf("With tax added: $%.2f", val * 1.13);
    return 0;
}
```
16.  
```c
#include <stdio.h>

int main(void) {
    printf("Enter the number of seconds to evaluate: ");
    int seconds;
    scanf("%d", &seconds);
    int minutes = seconds / 60;
    seconds %= 60;
    int hours = minutes / 60;
    minute %= 60;
    printf("In 100 seconds there is %d Hours, %d Minutes and %d Seconds.", hours, minutes, seconds );
    return 0;
}
```
17. 
```c
#include <stdio.h>

int main(void) {
    printf("Enter a dollar amount: ");
    int dollars;
    scanf("%d", &dollars);
    printf("$20 bills: ", dollars / 20);
    dollars %= 20;
    printf("$10 bills: ", dollars / 10);
    dollars %= 10;
    printf("$5 bills: ", dollars / 5);
    dollars %= 5;
    printf("$1 bills: ", dollars);
    return 0;
}
```

18.  
```c
#include <stdio.h>

int main(void) {
    printf("Enter the first complex number in the form Re+jIM: ");
    int real1, real2, imag1, imag2;
    scanf("%d+j%d", &real1, &imag1);
    printf("Enter the second complex number in the form Re+jIM: ");
    scanf("%d+j%d", &real2, &imag2);
    printf("The result is: ", real1 + real2, imag1 + imag2);
    return 0;
}
```