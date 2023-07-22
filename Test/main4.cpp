#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> commands;
unordered_map<string, int> funct;
vector<int> jump_back;
vector<string> in = {"MAIN"};

int main() {
    int t, n;
    cin >> t;
    cin.ignore();
    for(int i = 0; i < t; i++){
        cin >> n;
        cin.ignore();
        long long x = 0;
        for(int j = 0; j < n; j++){
            string command;
            getline(cin, command);
            commands.push_back(command);
        }
        //cout << endl;
        for(int j = 0; j < n; j++){
            //cout << commands[j];
            if(commands[j].substr(0, 3) == "ADD"){
                x += stoi(commands[j].substr(4));
            }else if(commands[j].substr(0, 3) == "SUB"){
                x -= stoi(commands[j].substr(4));
            }else if(commands[j].substr(0, 4) == "MULT"){
                x *= stoi(commands[j].substr(5));
            }else if(commands[j].substr(0, 3) == "FUN"){
                if(in.size() <= 1)
                    funct[commands[j].substr(4)] = j;
                int step = 1;
                j++;
                while(step){
                    if(commands[j].substr(0, 3) == "END") step--;
                    else if(commands[j].substr(0, 3) == "FUN"){
                        step++;
                        if(in.size() <= 1)
                            funct[commands[j].substr(4)] = j;
                    }
                    j++;
                }
                j--;
            }else if(commands[j].substr(0, 3) == "END"){
                j = jump_back.back();
                jump_back.pop_back();
                //if(jump_back.size() == 0);
            }else if(commands[j].substr(0, 4) == "CALL"){
                if(funct[commands[j].substr(5)] == 0){
                    if(commands[0].substr(0,3) == "FUN"){
                        in.push_back(commands[j].substr(5));
                        jump_back.push_back(j);
                        j = funct[commands[j].substr(5)];
                    }
                }else if(count(in.begin(), in.end(), commands[j].substr(5))){
                    continue;
                }else{
                    jump_back.push_back(j);
                    in.push_back(commands[j].substr(5));
                    j = funct[commands[j].substr(5)];
                }
            } 
        }
        commands.clear();
        cout << x % 1000000007 << '\n';
    }
    return 0;
}