// Written by Dallas Hart on 2023-01-20
// This program belongs to Assignment 3in ENGG*1420 at UOG
// Purpose: Make and use a "Rect" class which has multiple methods and l, w, and position

package q1_2;

// Class Rect which contains all methods the object will inherit
class Rect
{
    // The rectangle has position, length, and width
    int x, y, l, w;

    // Initialize all properties via constructor
    Rect(int x, int y, int l, int w)
    {
        this.x = x;
        this.y = y;
        this.l = l;
        this.w = w;
    }

    // Calculate perimeter of rectangle
    int getPerimeter()
    {
        return (l + w) * 2;
    }

    // Calculate area of rectangle
    int getArea()
    {
        return l * w;
    }

    // Change values for position
    void move(int x, int y)
    {
        this.x = x;
        this.y = y;
    }

    // Set length and width to n
    void changeSize(int n)
    {
        l = n;
        w = n;
    }

    // Print out all properties/values of the rectangle
    void print()
    {
        System.out.printf("Length: %d\tWidth: %d%n", l, w);
        System.out.printf("X: %d\t\tY: %d%n", x, y);
        System.out.printf("Perimeter: %d\tArea: %d%n", getPerimeter(), getArea());
    }
}

class Question1_2
{
    public static void main(String[] args)
    {
        // Initialize using constructor
        Rect rect = new Rect(5, 2, 7, 8);

        // Expect:
        // Length: 7       Width: 8
        // X: 5            Y: 2
        // Perimeter: 30   Area: 56 
        rect.print();
        
        // Change the x, y, l, w values of the rectangle
        rect.move(2, 10);
        rect.changeSize(4);
        
        // Expect:
        // Perimeter: 16
        // Area: 16
        System.out.printf("Perimeter: %d%n", rect.getPerimeter());
        System.out.printf("Area: %d%n", rect.getArea());

        // Expect:
        // Length: 4       Width: 4
        // X: 2            Y: 10
        // Perimeter: 16   Area: 16 
        rect.print();
    }
}
