#include "Question_2.cpp"
#include <vector>



int main(){
    DataStructure ds;
    std::vector<std::string> names = {
            "persian", "israeli", "german", "russian", "spanish", "italian", "greek", "hungarian",
            "brazilian", "turkish"
    };
    for(int i = 0; i < 10; i++)
        ds.Insert(i+10, names[i]);
    ds._inorder_print(ds.tree1.root);
    std::cout.flush();
    std::cout << "\n";
    for(int i = 5; i < 8; i++)
        ds.Delete(i);
    ds._inorder_print(ds.tree1.root);
    auto ma = ds.Max_Price();
    std::cout << "\nMax Price: " << ma << "\n";


    ds.Pick_Month_Hits(1, 10);
    ds.Show_Month_Hits();
    ds.End_Month();
}


