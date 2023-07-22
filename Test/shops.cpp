#include <iostream>
#include <vector>

#define for_i(x, y) for(int x = 0; x < y; x++)

using namespace std;

struct product{
    string name;
    double price;
    int quantity;    
};
bool operator==(product& a, product& b){
    return a.name == b.name;
}

int main(){
    vector<product> products;
    int num_of_stores;
    cin >> num_of_stores;
    for_i(i, num_of_stores){
        int num_of_items;
        cin >> num_of_items;
        for_i(j, num_of_items){
            product temp_product;
            cin.ignore();
            cin >> temp_product.name;
            cin.ignore();
            cin >> temp_product.price;
            cin >> temp_product.quantity;
            bool unique_flag = true;
            for(product& comp : products){
                if(comp == temp_product){
                    //cout << (comp.price*comp.quantity + temp_product.price*temp_product.quantity) / (comp.quantity + temp_product.quantity);
                    comp.price = (comp.price*comp.quantity + temp_product.price*temp_product.quantity) / (comp.quantity + temp_product.quantity);
                    comp.quantity += temp_product.quantity; 
                    unique_flag = false;
                    break;
                }
            }
            if(unique_flag)
                products.push_back(temp_product);
        }
        
    }
    for(product cur_product : products)
        cout << "name: " << cur_product.name << " Price: " << cur_product.price << " Quantity: " << cur_product.quantity << endl;
    

    cin.get();
    return 0;
}




