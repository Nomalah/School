// Written by Dallas Hart on 2023-02-01
// This program belongs to Assignment 4 in ENGG*1420 at UOG
// Purpose: Use RLE to encode a user inputted string

import java.util.Scanner;

class Question1_Assign4
{
    public static void main(String[] args)
    {
        // Grab user input
        Scanner scanner = new Scanner(System.in);
        String input = scanner.nextLine();

        // Run length encoding
        char last = '\0'; // Placeholder for first element
        int count = 1;
        for (int i = 0; i < input.length(); i++) {
            if (input.charAt(i) == last){ // Check if element is the same as the last
                count++;
            } else if (last != '\0') { // Only print for non placeholder elements
                // Print character/length for RLE
                System.out.print(last);
                if (count != 1) { // skip count if there is only 1.
                    System.out.print(count);
                    count = 1;
                }
            }
            last = input.charAt(i); // Update last element
        }
        // Print out last character/length combo
        System.out.print(last);
        if (count != 1) {
            System.out.print(count);
            count = 1;
        }

        // Add ending newline and close scanner
        System.out.println("");
        scanner.close();
    }
}
