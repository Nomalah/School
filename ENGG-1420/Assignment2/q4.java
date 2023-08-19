// Written by Dallas Hart on 2023-01-16
// This program belongs to Assignment 2 in ENGG*1420 at UOG
// Purpose: sum user inputted numbers until 0 is reached. using "while" and "break"

// import scanner utility
import java.util.Scanner;

class Question4
{
    public static void main(String[] args)
    {
        // Initialize scanner object to use to read user input
        Scanner scanner = new Scanner(System.in);
        int sum = 0; // initialize our sum
        // loop forever
        while (true)
        {
            System.out.print("Input number, enter 0 to exit: ");
            int num = scanner.nextInt(); // get user input
            // exit if user entered 0
            if (num == 0)
            {
                break;
            }
            sum += num; // sum user inputted number
        }
        // close out scanner
        scanner.close();
        // output sum
        System.out.printf("The sum is %d.%n", sum);
    }
}
