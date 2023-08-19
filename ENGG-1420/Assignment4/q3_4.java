// Written by Dallas Hart on 2023-02-01
// This program belongs to Assignment 4 in ENGG*1420 at UOG
// Purpose: Make and use a "Book" class which has multiple methods, with a title, author and other metadata

import java.util.stream.Stream;

// Class Date which contains all methods the object will inherit
class Book
{
    private String title;
    private String author;
    private int num_of_pages;
    private int year_of_publication;
    private float price;

    // Initialize all properties via constructor
    public Book(String title, String author, int num_of_pages, int year_of_publication, float price)
    {
        this.title = title;
        this.author = author;
        this.num_of_pages = num_of_pages;
        this.year_of_publication = year_of_publication;
        this.price = price;
    }

    // Constructor for missing author
    public Book(String title, int num_of_pages, int year_of_publication, float price)
    {
        this(title, "Anonymous", num_of_pages, year_of_publication, price);
    }

    // Constructor for missing identification
    public Book(int num_of_pages, int year_of_publication, float price)
    {
        this("Unknown", "Anonymous", num_of_pages, year_of_publication, price);
    }

    // Get the title in title case
    public String getTitleinTitleCase()
    {
        String[] title_words = title.split(" "); // Split the string with spaces as the delimiter
        String[] capitalized = Stream.of(title_words).map( // Map every word in the title
            str -> str.substring(0, 1).toUpperCase() + str.substring(1) // Capitalize string
        ).toArray(String[]::new); // Convert back to an array of strings
        return String.join(" ", capitalized); // Add back the spaces
    }

    // Check if the title contains a string
    public boolean contains(String to_match)
    {
        return title.contains(to_match);
    }

    // Print all the authors on separate lines
    public void printAuthors()
    {
        System.out.println(author.replace(",", "\n")); // Replace all commas with newlines
    }
}

class Question3_4_Assign4
{
    public static void main(String[] args)
    {
        // Example for Book class
        Book book = new Book("how to be built diff", "joe,jack,a;fdkaj; afd;slkj;,too", 0, 0, 0);
        System.out.println(book.getTitleinTitleCase());
        book.printAuthors();
    }
}
