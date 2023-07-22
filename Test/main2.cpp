#include <iostream>
#include <vector>

using namespace std;

struct store{
    int num_items;
    vector<string> item_name;
    vector<int> item_cost;
    vector<int> item_quantity;
};

int main(){
    int t;
    cin >> t;
    cin.ignore();
    for(int i = 0; i < t; i++){
        //cout << "here1";
        int num_of_stores;
        cin >> num_of_stores;
        vector<store> stores;
        for(int q = 0; q < num_of_stores; q++){
            //cout << "here2";
            store temp_store;
            cin >> temp_store.num_items;
            //cout << temp_store.num_items;
            cin.ignore();
            //cout << temp_store.num_items;
            for(int p = 0; p < temp_store.num_items; p++){
                //cout << "here3 " << p;
                string temp_item_name;
                cin >> temp_item_name;
                cin.ignore();
                //cout << "here4";
                int temp_item_cost, temp_item_quantity;
                cin >> temp_item_cost >> temp_item_quantity;
                cin.ignore();
                //cout << "here5";
                temp_store.item_name.push_back(temp_item_name);
                temp_store.item_cost.push_back(temp_item_cost);
                temp_store.item_quantity.push_back(temp_item_quantity);
            }
            //cout << "what is going on?";
            stores.push_back(temp_store);
        }
        int cost = 0;
        int o = 0;
        int k;
        cin >> k;
        //cout << "what is going on?";
        for(int p = 0; p < k; p++){
            string item_name;
            cin >> item_name;
            cin.ignore();
            int item_quantity;
            cin >> item_quantity;
            cin.ignore();
            //cin >> o;
            while(item_quantity != 0){
                int best_price = 0x7FFFFFFF;
                int best_store;
                int product;
                //cin >> o;
                for(int q = 0; q < stores.size(); q++){
                    for(int z = 0; z < stores[q].num_items; z++){
                        if(stores[q].item_name[z] == item_name){
                            if(stores[q].item_cost[z] < best_price){
                                best_price = stores[q].item_cost[z];
                                best_store = q;
                                product = z;
                                break;
                            }
                        }
                    }
                }
                //cin >> o;
                cost += min(stores[best_store].item_quantity[product], item_quantity) * stores[best_store].item_cost[product];
                item_quantity -= min(stores[best_store].item_quantity[product], item_quantity);
                stores[best_store].item_quantity.erase(stores[best_store].item_quantity.begin() + product);
                stores[best_store].item_name.erase(stores[best_store].item_name.begin() + product);
                stores[best_store].item_cost.erase(stores[best_store].item_cost.begin() + product);
                stores[best_store].num_items--;
                //cout << "here";
            }
        }
        cout << cost << '\n';

    }
    return 0;
}