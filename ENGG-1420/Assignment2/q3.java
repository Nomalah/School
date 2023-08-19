// Written by Dallas Hart on 2023-01-16
// This program belongs to Assignment 2 in ENGG*1420 at UOG
// Purpose: manipulate if-else statements to achieve desired results

class Question3
{
    // Solution for part A
    public static void partA()
    {
        System.out.println( "Part A:" );
        int x = 5;
        int y = 8;
        if ( y == 8 )
        {
            if ( x == 5 )
            {
                System.out.println( "@@@@@" );
            } else
            {
                System.out.println( "#####" );
            }
        }
        System.out.println( "$$$$$" );
        System.out.println( "&&&&&" );
    }

    // Solution for part B
    public static void partB() 
    {
        System.out.println( "Part B:" );
        int x = 5;
        int y = 8;
        if ( y == 8 )
        {
            if ( x == 5 )
            {
                System.out.println( "@@@@@" );
            }
        } else
        {
            System.out.println( "#####" );
            System.out.println( "$$$$$" );
            System.out.println( "&&&&&" );
        }
    }

    // Solution for part C
    public static void partC()
    {
        System.out.println( "Part C:" );
        int x = 5;
        int y = 7;
        if ( y == 8 )
        {
            if ( x == 5 )
            {
                System.out.println( "@@@@@" );
            }
        } else
        {
            System.out.println( "#####" );
            System.out.println( "$$$$$" );
            System.out.println( "&&&&&" );
        }
    }

    public static void main(String[] args)
    {
        // Run all 3 parts
        partA();
        partB();
        partC();
    }
}
