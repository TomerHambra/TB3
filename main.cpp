#include "Question_2.cpp"
#include <vector>

/****************************************************************************
                    I  N  F  O  R  M  A  T  I  O  N

        Lia Bercovitz - 328381926
        Tomer Hambra - 216634758

        Due Date - 7.5.24
        Submitted to Jonatan Sperber
****************************************************************************/

// Test for Q2

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


