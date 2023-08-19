// Written by Dallas Hart on 2023-01-20
// This program belongs to Assignment 3 in ENGG*1420 at UOG
// Purpose: Make and use a "Date" class which has multiple methods and a day, year and month

package q3_4;

// Class Date which contains all methods the object will inherit
class Date
{
    // The rectangle has position, length, and width
    int month, day, year;

    // Initialize all properties via constructor
    public Date(int month, int day, int year)
    {
        this.month = month;
        this.day = day;
        this.year = year;
    }

    // Add a single day to the date
    private void addDay()
    {
        // Case for the new year
        if (this.month == 12 && this.day == 31)
        {
            // Jan 1
            this.month = 1;
            this.day = 1;
            this.year += 1; 
            return;
        }

        // All end of month cases
        int[] last_day_of_months = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
            
        if (last_day_of_months[this.month - 1] == this.day)
        {
            // Next month (same year)
            this.month += 1;
            this.day = 1;
            return;
        }

        // Next day (same year & month)
        this.day += 1;
    }

    // Iteratively add days to the date
    public void addDays(int n) {
        for (int i = 0; i < n; i++) {
            addDay();
        }
    }

    // Check if one date is less then another
    private boolean lessThen(Date other) {
        // Check if both dates are equal
        if (this.year == other.year && this.month == other.month && this.day == other.day)
        {
            return false;
        }
        // If the years are different, there's a result
        if (this.year < other.year)
        {
            return true;
        }
        // Logic for determining month & day, to see if this < other
        if (this.year == other.year && (this.month < other.month || (this.month == other.month && this.day < other.day)))
        {
            return true;
        }
        return false;
    }

    // Calculate the number of days between two dates
    public int compare(Date other) {
        Date earlier;
        Date later;
        // Determine which date is earlier
        if (this.lessThen(other)){
            earlier = this;
            later = other;
        } else {
            earlier = other;
            later = this;
        }
        // (Create new earlier date as it must be able to change)
        earlier = new Date(earlier.month, earlier.day, earlier.year);

        // Iteratively count up the days until earlier == later
        int difference = 0;
        while (earlier.year != later.year || earlier.month != later.month || earlier.day != later.day){
            earlier.addDay();
            difference += 1;
        }
        return difference;
    }

    // Print out all properties/values of the date
    void print()
    {
        System.out.printf("(MM/DD/YYYY) %02d/%02d/%04d%n", month, day, year);
    }
}

class Question3_4
{
    public static void main(String[] args)
    {
        // Initialize using constructor
        Date date1 = new Date(12, 22, 2004);

        // Expect:
        // (MM/DD/YYYY) 12/22/2004 
        date1.print();
        
        // Add 100 days to date1
        date1.addDays(100);

        // Expect:
        // (MM/DD/YYYY) 04/01/2005
        date1.print();

        Date date2 = new Date(11, 20, 2003);
        
        // Expect:
        // (MM/DD/YYYY) 11/20/2003
        date2.print();
        
        // Print the number of days between date1 and date2
        // Expect:
        // 497
        System.out.printf("Number of days between date1 and date2: %d%n", date1.compare(date2));
        
        // Add 100 days to date2
        date2.addDays(100);

        // Expect:
        // (MM/DD/YYYY) 02/28/2004
        date2.print();

        // Print the number of days between date1 and date2
        // Expect:
        // 397
        System.out.printf("Number of days between date1 and date2: %d%n", date1.compare(date2));
    }
}
