// Written by Dallas Hart on 2023-02-01
// This program belongs to Assignment 4 in ENGG*1420 at UOG
// Purpose: Implement random string class with function nextString which returns a random string of a given length

import java.util.Random;

// Random string class (purely static)
class RandomString {
    private static Random random = new Random(); // Random number generator
    public static String nextString(int n) {
        StringBuilder builder = new StringBuilder();
        for (int i = 0; i < n; i++){
            int ascii = 0;
            // Generate random numbers until inside bounds
            while (!((ascii >= '0' && ascii <= '9') || (ascii >= 'a' && ascii <= 'z') || (ascii >= 'A' && ascii <= 'Z') )) {
                ascii = random.nextInt(128); // Generate numbers between 0-127 (inside ascii bounds)
            }
            builder.append((char)ascii); // Add the character to the string
        }

        return builder.toString(); // Convert to string and return
    }
}

class Question2_Assign4
{
    public static void main(String[] args)
    {
        // Example for RandomString
        for (int i = 5; i <= 10; i++){
            System.out.println(RandomString.nextString(i));
        }
    }
}
