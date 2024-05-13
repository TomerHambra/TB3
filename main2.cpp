#include "Question_3.cpp"
#include <vector>

void _inorder_print(avl_tree_node<Record> * node){
    if(node == nullptr) return;
    _inorder_print(node->left);
    std::cout << node->value << " " << node->height << "\n";
    _inorder_print(node->right);
}

//TODO: Problems:
//    rank is not done properly, j = 4 yields third         -fixed
//    split is done without order apparently                -maybe fixed??
//    max is not updated correctly                          -fixed
//    problem with the max system?                          -fixed

int main(){
    DataStructure ds;
    std::vector<std::string> names = {
            "persian", "israeli", "german", "russian", "spanish", "italian", "greek", "hungarian",
            "brazilian", "turkish"
    };
    for(int i = 0; i < 10; i++)
        ds.Insert(i+10, names[i], 1);
    _inorder_print(ds.series[0]->tree1.root);
    for(int i = 5; i < 8; i++)
        ds.Delete(i, 1);
    _inorder_print(ds.series[0]->tree1.root);
    auto ma = ds.Max(1);
    std::cout << "\nMax Price: " << ma << "\n\n\n";
    ds.Split_Series(1, 4);
    _inorder_print(ds.series[0]->tree1.root);
    auto r = ds.Max(1);
    std::cout << "\n\n\n" << r<< " \n\n\n";
    _inorder_print(ds.series[1]->tree1.root);
    ma = ds.Max();
    std::cout << "\nTotal Max Price: " << ma << "\n";
    _inorder_print(ds.all_records.root);
}
