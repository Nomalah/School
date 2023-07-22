#include <iostream>

// std::vector
#include <vector>

// std::sort
#include <algorithm>
// std::function
#include <functional>

// These are for the random numbers
#include <time.h>
#include <cstdlib>

// This swaps 2 values of any type
#define my_swap(a, b) {     \
    auto _c_ = a;          \
    a = b;                  \
    b = _c_;                \
}

using namespace std;

// A structure of a student
struct s_student{ 
    int age; // Student's age
    float cur_mark; // Student's current mark
    vector<float> marks; // Student's marks
    int identifier; // Student's identifier/name
};

// A class of a student
class c_student{
    private:
        int age; // Student's age
        float cur_mark; // Student's current mark
        vector<float> marks; // Student's marks
    public:
        int identifier; // Student's idenitifer/name

        // Constuctor with initializer list
        c_student(int initial_identifier, int initial_age, float initial_mark, vector<float> initial_marks) 
            : identifier(initial_identifier), age(initial_age), cur_mark(initial_mark), marks(initial_marks){
        }

        // Getters and Setters for age and marks
        void set_age(unsigned int s_age){age = s_age;}
        int get_age(){return age;}
        void set_mark(float s_mark){cur_mark = s_mark;}
        float get_mark(){return cur_mark;}

        // Print the student's mark along with their idenitier
        void print_marks(){
            cout << "Student " << identifier << " marks" << endl;
            for(float mark : marks)
                // Put a Tab infront to signify which student it is from
                cout << '\t' << mark << endl;
        }

        // Take the average of all the student's marks
        void calc_new_mark(){
            float total = 0;
            for(float mark : marks)
                total += mark;

            // Set the student's current mark to the average
            cur_mark = total/marks.size();
        }

        // Sort the marks based on a user defined comparison (takes in 2 marks and returns a boolean)
        void sort_marks(function<bool(float,float)> comparison){
            for(int j = 0; j < marks.size(); j++)
                for(int i = 0; i < marks.size()-1; i++)
                    if(comparison(marks[i], marks[i+1])) 
                        // swap the 2 marks
                        my_swap(marks[i], marks[i+1]);
        }

};

int main(){
    // Declare a structure version of a student with initalizer lists
    // you have to initialize the variables in order
    s_student joe = {5, 90, {85, 92, 90, 25, 80, 99, 98}, 20};

    // you can set it's variables like this
    joe.age = 16;
    joe.cur_mark = 87;
    joe.marks = {85, 92, 90, 25, 80, 99, 98};

    // print the number of marks
    cout << "size of the vector: " << joe.marks.size() << endl;

    // iterator for loop to print all the marks
    for(float mark : joe.marks){
        cout << "mark" << " = " << mark  << endl;
    }
    cout << endl;

    // sort the numbers from greatest to least
    //greater<float>() = [](float mark_a, float mark_b) -> bool { return mark_a < mark_b;}
    sort(joe.marks.begin(), joe.marks.end(), greater<float>());

    // remove the last mark
    joe.marks.pop_back();

    // print the marks
    for(float mark : joe.marks)
        cout << "mark" << " = " << mark  << endl;

    // Calculate the average and set the current mark to it
    float total = 0;
    for(float mark : joe.marks)
        total += mark;

    joe.cur_mark = total/joe.marks.size();

    cout << "new mark is: " << joe.cur_mark << endl;

    // Student identifier = 20
    // Age = 15
    // Current mark = 85.7
    // Marks = {85, 92, 90, 25, 80, 99, 98}
    c_student student(20, 15, 85.7, {85, 92, 90, 25, 80, 99, 98});
    student.set_age(16);

    // Print the student's age, and starting mark & marks
    cout << "age: " << student.get_age() << endl;
    cout << "mark: " << student.get_mark() << endl;
    student.print_marks();

    // Calculate new mark and print it
    student.calc_new_mark();
    cout << "mark: " << student.get_mark() << endl;
    
    // sort the student's marks from greatest to least
    student.sort_marks(
        // Lambda to return the greater of the 2 inputs 
        [](float mark_a, float mark_b) -> bool {
            return mark_a < mark_b;
        }
    );

    // Print the student's marks from greatest to least
    student.print_marks();

    // Seed the random function with the current time
    srand(time(NULL));

    // Array of students
    vector<c_student> students;

    // Try to reserve space for 10 students
    students.reserve(10);

    // Generate 10 students
    for(int i = 0; i < 10; i++){
        // Give each student 5 marks
        vector<float> temp_marks;
        // Try to reserve space for 5 marks
        temp_marks.reserve(5);
        for(int j = 0; j < 5; j++)
            // Generate a mark between 100.00 and 45.00 and push it to the student's marks
            temp_marks.push_back((float)(10000 - rand()%5501)/100.0);

        // Generate the student with identifier i+1, age 10-14 current mark 0 and the marks previously generated
        c_student temp(i+1, rand() % 5 + 10, 0, temp_marks);

        // Push the student to the main vector
        students.push_back(temp);
    }

    // Print out the students marks
    for(c_student cur_student : students){
        // Calculate the current student's mark based on his returned marks
        cur_student.calc_new_mark();

        // Print the student's current mark/average
        cout << "Student " << cur_student.identifier << " cur_mark = " << cur_student.get_mark() << endl;

        // Sort his marks from smallest to largest
        cur_student.sort_marks([](float mark_a, float mark_b) -> bool {return mark_a > mark_b;});

        // Print the current student's marks
        cur_student.print_marks();
        
        // Put a space between students
        cout << endl;
    }

    // sort greatest to least
    sort(students.begin(), students.end(),
        // Lambda that takes in 2 elements from the vector, and returns if a's mark is greater then b's mark
        [](c_student a, c_student b) -> bool{
            return a.get_mark() > b.get_mark();
        }
    );
    
    // Iterator for loop
    for(c_student cur_student : students)
        // Print each students marks but in order from greatest to least
        cout << "Student " << cur_student.identifier << " cur_mark = " << cur_student.get_mark() << endl;

    // Wait for input
    std::cin.get();
    return 0;
}