#include <iostream>
#include <unordered_map>

using namespace std;

unordered_map<string, int> notes = {
    {"C", 0}, 
    {"C#", 1}, 
    {"D", 2}, 
    {"D#", 3}, 
    {"E", 4}, 
    {"F", 5}, 
    {"F#", 6}, 
    {"G", 7}, 
    {"G#", 8}, 
    {"A", 9}, 
    {"A#", 10}, 
    {"B", 11}
};

string base_notes[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

int main() {
    int t;
    cin >> t;
    cin.ignore();
    for(int i = 0; i < t; i++){
        string in_notes[4];
        for(int p = 0; p < 4; p++)
            cin >> in_notes[p];
        // base;
        if((notes[in_notes[0]] + 4) % 12 == notes[in_notes[1]]){
            if((notes[in_notes[1]] + 3) % 12 == notes[in_notes[2]]){
                if((notes[in_notes[2]] + 3) % 12 == notes[in_notes[3]]){
                    cout << "root";
                    continue;
                }
            }
        }

        // shift 1;
        if((notes[in_notes[3]] + 4) % 12 == notes[in_notes[0]]){
            if((notes[in_notes[0]] + 3) % 12 == notes[in_notes[1]]){
                if((notes[in_notes[1]] + 3) % 12 == notes[in_notes[2]]){
                    cout << "first";
                    continue;
                }
            }
        }

        // shift 2
        if((notes[in_notes[2]] + 4) % 12 == notes[in_notes[3]]){
            if((notes[in_notes[3]] + 3) % 12 == notes[in_notes[0]]){
                if((notes[in_notes[0]] + 3) % 12 == notes[in_notes[1]]){
                    cout << "second";
                    continue;
                }
            }
        }
        // shift 3

        if((notes[in_notes[1]] + 4) % 12 == notes[in_notes[2]]){
            if((notes[in_notes[2]] + 3) % 12 == notes[in_notes[3]]){
                if((notes[in_notes[3]] + 3) % 12 == notes[in_notes[0]]){
                    cout << "third";
                    continue;
                }
            }
        }
        cout << "invalid";     
    }
    return 0;
}