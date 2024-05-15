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

    bool operator<(Record& other) const{
        return serial_number < other.serial_number;
    }
    friend std::ostream& operator<<(std::ostream& os, Record& r){
        os << "Record: \nserial number: " << r.serial_number
           << " price: " << r.price << " name: " << r.name;
        return os;
    }
} Record;



void update(avl_tree_node<Record> * node){
    auto max_price = node->value;
    if(node->left != nullptr) max_price = node->left->_max.price < max_price.price ? max_price : node->left->_max;
    if(node->right != nullptr) max_price = node->right->_max.price < max_price.price ? max_price : node->right->_max;
    node->_max = max_price;
}


/****************************************************************************
       F  I  N  A  L      D  A  T  A      S  T  R  U  C  T  U  R  E
****************************************************************************/

/**------------------------- Question 1 ----------------------------------**/

typedef struct DataStructure {
    /*
     * Solution:
     *      We will use an avl tree of Records, where a record is a struct holding a serial number, a name, and a price.
     *      The avl tree is ordered by serial number, and each node holds a field called _max. This field is updated
     *      alongside the height and count fields, and it holds the record which has the maximum price in that node’s
     *      subtree (i.e. root->_max is the max price record in the entire tree). The reason this works is that when we
     *      insert a record which is bound to be the next max_price, this field only updates in that new node's search
     *      path, and since then we can just update it in the back side of the recursion of insert. In this way
     *      insertion, deletion and max_price become trivial, since they are straight from the lectures or just accessing a field.
     */

    avl_tree<Record> tree1{&update};
    Record max_price = {-1, -1, ""};
    int last_serial_number = 1;

    DataStructure() = default;
    ~DataStructure() = default;

    // Time Complexity: O(1)
    void Init() {
        max_price = {-1, -1, ""};
    }

    // Time Complexity: O(log n)
    void Insert(int price, std::string name) {
        Record record = {last_serial_number++, price, name};
        tree1.insert(record);
        max_price = tree1.root->_max;
    }

    // Time Complexity: O(log n)
    Record Delete(int number) {
        // changed the return value to the Record details we just deleted.
        // keep in mind that the search is done only using the serial number
        Record dummy = {number, -1, ""};
        auto temp = tree1.find(dummy);
        if(temp == nullptr) return {-1, -1, ""}; // no need to delete something that is not in the trees.
        Record record = temp->value;

        tree1.remove(record);
        max_price = tree1.root->_max; // the max node is updated inside the avl tree which is blackboxed out,
        // so we just access the inside field.
        return record;
    }

    // Time Complexity: O(1)
    Record Max_Price() {
        if(max_price.serial_number == -1)
            std::cout << "No elements in the data structure, so default max_price is returned." << std::endl;
        return this->max_price;
    }

} DataStructure;