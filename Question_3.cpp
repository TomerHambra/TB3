#include "data_structures_library.cpp"

/****************************************************************************
                    I  N  F  O  R  M  A  T  I  O  N

        Lia Bercovitz - 328381926
        Tomer Hambra - 216634758

        Due Date - 7.5.24
        Submitted to Jonatan Sperber
****************************************************************************/


/****************************************************************************
                C  O  N  T  A  I  N  E  R      T  Y  P  E  S
****************************************************************************/


typedef struct Record{
    int serial_number;
    int price;
    std::string name;

    bool operator<(Record& other){
        return serial_number < other.serial_number;
    }
} Record;


/**---------------------- Helper functions -------------------------------**/

void update(avl_tree_node<Record> * node){
    auto max_price = node->value;
    if(node->left != nullptr) max_price = node->left->value.price < node->value.price ? node->value : node->left->value;
    if(node->right != nullptr) max_price = node->right->value.price < node->value.price ? node->value : node->right->value;
    node->_max = max_price;
}


/**------------------------------- & -------------------------------------**/

typedef struct SeriesElements {
    /** Since the data structure from question 1 is helpful here, were just going to copy the code from there **/

    avl_tree<Record> tree1{&update};
    Record max_price = {-1, -1, ""};
    int next_serial_number = 1;


    SeriesElements() = default;
    ~SeriesElements() = default;

    void Init(){
        max_price = {-1, -1, ""};
        next_serial_number = 1;
    }

    void Insert(int price, std::string name){
        Record record = {next_serial_number++, price, name};
        tree1.insert(record);
    }

    void Delete(int number){
        // keep in mind that the search is done only using the serial number
        Record dummy = {number, -1, ""};
        auto temp = tree1.find(dummy);
        if(temp == nullptr) return; // no need to delete something that is not in the trees.
        Record record = temp->value;

        tree1.remove(record);
        max_price = tree1.root->_max;
    }

    Record Max_Price() {
        if(max_price.serial_number == -1)
            std::cout << "No elements in the data structure, so default max_price is returned." << std::endl;
        return this->max_price;
    }
} SeriesElements;


typedef struct SeriesNode {



} SeriesNode;



/****************************************************************************
       F  I  N  A  L      D  A  T  A      S  T  R  U  C  T  U  R  E
****************************************************************************/

/**------------------------- Question 3 ----------------------------------**/

typedef struct DataStructure {


} DataStructure;
