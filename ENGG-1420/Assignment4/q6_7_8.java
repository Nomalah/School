// Written by Dallas Hart on 2023-02-01
// This program belongs to Assignment 4 in ENGG*1420 at UOG
// Purpose: Create circle class which can sum together radii and decompose into it's component circles

import java.util.Random;
import java.util.ArrayList;

class Circle
{
    private int radius;
    public Circle(int radius)
    {
        this.radius = radius;
    }

    public void add(Circle other)
    {
        this.radius += other.radius; // Add radii together
    }

    public void addAll(Circle[] others)
    {
        for (Circle other : others) this.add(other); // Add all circles to the current one
    }

    // Question 8
    public ArrayList<Circle> decompose()
    {
        ArrayList<Circle> constituents = new ArrayList<Circle>(); // Must be mutable array
        int temp_radius = this.radius;
        for (int i = 2; i <= temp_radius; ) {
            if (temp_radius % i == 0) { // A circle is a constituent if it's a prime factor
                temp_radius /= i; // Divide out factor
                constituents.add(new Circle(i)); // Add a circle with the factor as it's radius
            } else i++; // Only check the next number if the current one was not divisible
        }
        return constituents;
    }

    // Question 7
    public static void main(String[] args)
    {
        // Generate 100 circles with radius 1-100
        Circle[] circles = new Circle[100];
        for (int i = 1; i <= 100; i++) circles[i - 1] = new Circle(i);
        
        // Generate circle with random number
        Random random = new Random();
        Circle C = new Circle(random.nextInt(10, 1001));
        System.out.printf("Circle radius before: %d%n", C.radius);
        C.addAll(circles);
        System.out.printf("Circle radius after: %d%n", C.radius);
        
        // Print circle constituents radii
        System.out.print("Radii of constituents: ");
        for (Circle circle : C.decompose())
        {
            System.out.printf("%d, ", circle.radius); 
        }
        System.out.println("");
    }
}
