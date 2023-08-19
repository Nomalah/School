#include <iostream>
#include <iomanip>

void find_total(int* dice_totals, int running_total, int num_of_dice, int start_num_of_dice){
    if(num_of_dice == 0)
        dice_totals[running_total-start_num_of_dice]++;
    else
        for(int i = 1; i <= 6; i++)
            find_total(dice_totals, running_total + i, num_of_dice - 1, start_num_of_dice);
}

int main(){
    int num_of_dice;
    std::cin >> num_of_dice;
    int* dice_totals = new int[num_of_dice*6-num_of_dice+1];
    for(int i = 0; i < num_of_dice*6-num_of_dice+1; i++){
        dice_totals[i] = 0;
    }
    find_total(dice_totals, 0, num_of_dice, num_of_dice);

    for(int i = 0; i < num_of_dice*6-num_of_dice+1; i++)
        std::cout << std::setw(5) << i + num_of_dice << std::setw(5) << " | " << std::setw(10) << dice_totals[i] << std::endl;
    
    return 0;
}