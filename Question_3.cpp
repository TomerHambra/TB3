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
    friend std::ostream& operator<<(std::ostream& os, Record& r){
        os << "Record: \nserial number: " << r.serial_number
           << " price: " << r.price << " name: " << r.name;
        return os;
    }
} Record;


/**---------------------- Helper functions -------------------------------**/

void update(avl_tree_node<Record> * node){
    auto max_price = node->value;
    if(node->left != nullptr) max_price = node->left->_max.price < max_price.price ? max_price : node->left->_max;
    if(node->right != nullptr) max_price = node->right->_max.price < max_price.price ? max_price : node->right->_max;
    node->_max = max_price;
}

/**------------------------------- & -------------------------------------**/

typedef struct SeriesElements {
    // This is essentially the same code as Question 1 besides the serial number bit brought out.

    avl_tree<Record> tree1{&update};
    Record max_price = {-1, -1, ""};


    SeriesElements() = default;
    ~SeriesElements() = default;

    SeriesElements(avl_tree_node<Record> * new_root) {
        tree1.root = new_root;
        tree1._size = new_root->count;
        max_price = new_root->_max;
    }

    void Init(){
        max_price = {-1, -1, ""};
    }

    void Insert(int serial_number, int price, std::string name){
        Record record = {serial_number, price, name};
        tree1.insert(record);
        max_price = tree1.root->_max;
    }

    Record Delete(int number){ // changed the return value to the Record details we just deleted.
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

    Record Max_Price() {
        max_price = this->tree1.root->_max;
        if(max_price.serial_number == -1)
            std::cout << "No elements in the data structure, so default max_price is returned." << std::endl;
        return this->max_price;
    }
} SeriesElements;





/****************************************************************************
       F  I  N  A  L      D  A  T  A      S  T  R  U  C  T  U  R  E
****************************************************************************/

/**------------------------- Question 3 ----------------------------------**/

typedef struct DataStructure {
    /*
     * Solution:
     *      We will maintain a dynamic array of the struct 'SeriesElements' which is a struct including an avl tree which is
     *      ordered by serial number, and has all the functionalities of the DataStructure from Question_1.cpp.
     *      With that, we will also keep an avl tree including all records and updates the max price in subtree,
     *      and a field 'last_serial_number' which holds the current last_serial_number.
     *      A further Complexity Analysis for the Time complexity of the function 'Split_Series(i, j)' will be provided
     *      above the function declaration.
     */

    dynamic_array<SeriesElements * > series;
    avl_tree<Record> all_records{&update};
    int last_serial_number;

    // This functions as the Init() simply because there is no reason to do a separate Init function...
    // Time Complexity: O(1)
    DataStructure() {
        last_serial_number = 1;
        series.insert_last(new SeriesElements());
    }

    // Time complexity: O(n)
    ~DataStructure(){
        for(int i = 0; i < series.size(); i++)
            delete series[i];
    }

    // Time Complexity: O(log n)
    void Insert(int price, std::string name, int i){
        if(i < 1 || series.size() < i) return; // protecting from segfaults due to array out of index.
        series[i-1]->Insert(last_serial_number, price, name);
        all_records.insert({last_serial_number++, price, name});
    }

    // Time Complexity: O(log n)
    void Delete(int number, int i) {
        if(i < 1 || series.size() < i) return; // protecting from segfaults due to array out of index.
        auto rec = series[i-1]->Delete(number);
        all_records.remove(rec);
    }

    // Time Complexity: O(1)
    Record Max(int i){
        if(i < 1 || series.size() < i) return {-1, -1, ""}; // protecting from segfaults due to array out of index.
        return series[i-1]->Max_Price();
    }

    /*
     * Complexity Analysis:
     *      The time complexity of the split algorithm is O(log n) as shown in lectures. Let c be an integer s.t.
     *      T(Split_Series) <= c * (log n) for all n greater than some integer N. If we use the accounting method, we
     *      will see that the Insert() method 'pays' for the Split_Series() Method, if we expand its constant by c.
     *      Overall we get that the accounting method yields a complexity of O(1) amortized for this function (since the
     *      amount of splits is bounded by n, the amount of elements).
     */
    // Time Complexity: O(log n), but O(1) amortized
    void Split_Series(int i, int j){
        if(i < 1 || series.size() < i) return; // protecting from segfaults due to array out of index.
        if(series[i-1]->tree1.size()< 2) return; // important for clarifying the proof.
        auto node = series[i-1]->tree1.node_by_rank(j);
        auto root2 = series[i-1]->tree1.split(node);
        series.insert_last(new SeriesElements(root2));
        series[i-1]->max_price = series[i-1]->tree1.root->_max;
        series.last()->max_price = series.last()->tree1.root->_max;
    }

    // Time Complexity: O(1)
    Record Max() { // Bonus  :)
        auto ma = all_records.root->_max;
        if(ma.serial_number == -1)
            std::cout << "No elements in the data structure, so default _max is returned." << std::endl;
        return ma;
    }

} DataStructure;
