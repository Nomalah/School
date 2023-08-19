// Written by Dallas Hart on 2023-02-01
// This program belongs to Assignment 4 in ENGG*1420 at UOG
// Purpose: Split a string of emails and count the number with underscores and the number that are gmail accounts

import java.util.Scanner;

class Question5_Assign4
{
    public static void main(String[] args)
    {
        // Grab list of emails (as a string) from user
        Scanner scanner = new Scanner(System.in);
        String input = scanner.nextLine();
        scanner.close();
        
        String[] emails = input.split("[ ;,]"); // Split the emails into an array

        // Count up underscores and gmail accounts
        int underscore_count = 0; 
        int gmail_count = 0; 
        for (String email : emails)
        {
            if (email.contains("_")) underscore_count++;
            if (email.endsWith("@gmail.com")) gmail_count++;
        }

        // Print out result
        System.out.printf("Underscore email count: %d%nGmail email count: %d%n", underscore_count, gmail_count);
    }
}
