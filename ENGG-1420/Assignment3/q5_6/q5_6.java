package q5_6;
// Written by Dallas Hart on 2023-01-20
// This program belongs to Assignment 3 in ENGG*1420 at UOG
// Purpose: Make and use a "Rect" class which has multiple methods and l, w, and position, and has proper access modifiers

// Class Rect which contains all methods the object will inherit
class Rect
{
    // The rectangle has position, length, and width
    private int x, y, l, w;

    // Initialize all properties via constructor
    public Rect(int x, int y, int l, int w)
    {
        this.x = x;
        this.y = y;
        // Bound l & w to be positive and non-zero
        this.l = Rect.bound(l);
        this.w = Rect.bound(w);
    }

    // Constructor which only takes length and width
    public Rect(int l, int w)
    {
        this(0, 0, l, w);
    }

    // Calculate perimeter of rectangle
    public int getPerimeter()
    {
        return (l + w) * 2;
    }

    // Calculate area of rectangle
    public int getArea()
    {
        return l * w;
    }

    // Change values for position
    public void move(int x, int y)
    {
        this.x = x;
        this.y = y;
    }

    // Set length and width to n
    public void changeSize(int n)
    {
        n = Rect.bound(n); // Bound l & w to be positive and non-zero
        l = n;
        w = n;
    }

    // Private function to handle bounding the length and width of the rectangle
    private static int bound(int n) {
        if (n < 0)
            return -n;
        if (n == 0)
            return 1;
        return n;
    }

    // Print out all properties/values of the rectangle
    public void print()
    {
        System.out.printf("Length: %d\tWidth: %d%n", l, w);
        System.out.printf("X: %d\t\tY: %d%n", x, y);
        System.out.printf("Perimeter: %d\tArea: %d%n", getPerimeter(), getArea());
    }

    // Compares area of itself against another Rect
    public boolean isBiggerThan(Rect other)
    {
        return this.getArea() > other.getArea();
    }
}

class Question5_6
{
    public static void main(String[] args)
    {
        // Initialize scanner object to use to read user input
        Rect rect2 = new Rect(5, 2, 7, 8);
        Rect rect1 = new Rect(4, 3);

        // Expect:
        // Length: 4       Width: 2
        // X: 0            Y: 0
        // Perimeter: 14   Area: 12
        rect1.print();

        // Expect:
        // Length: 7       Width: 8
        // X: 5            Y: 2
        // Perimeter: 30   Area: 56 
        rect2.print();
        
        // Change the x, y, l, w values of the rectangle 
        rect2.move(2, 10);
        rect2.changeSize(0); // Showcase bounding on l & w
        
        // Expect:
        // Perimeter: 4
        // Area: 1
        System.out.printf("Perimeter: %d%n", rect2.getPerimeter());
        System.out.printf("Area: %d%n", rect2.getArea());

        // Change size to regular value
        rect2.changeSize(3);

        // Expect:
        // Length: 3       Width: 3
        // X: 2            Y: 10
        // Perimeter: 12   Area: 9 
        rect2.print();

        // Expect:
        // true
        System.out.printf("Rect1.area > Rect2.area: %b%n", rect1.isBiggerThan(rect2));
    }
}
