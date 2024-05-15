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

    bool operator<(Record& other) const {
        return serial_number < other.serial_number;
    }
    friend std::ostream& operator<<(std::ostream& os, Record& r){
        os << "Record: \nserial number: " << r.serial_number
            << " price: " << r.price << " name: " << r.name;
        return os;
    }

    Record& operator=(Record other){
        serial_number = other.serial_number;
        price = other.price;
        name = other.name;
        return *this;
    }

} Record;


typedef struct PriceNode {
    int price;
    avl_tree<Record> * records_tree;

    explicit PriceNode(int price) : price(price), records_tree(nullptr) {
        records_tree = new avl_tree<Record>();
    };

    ~PriceNode(){
        delete records_tree;
    }

    bool operator<(PriceNode& other) const {
        return price < other.price;
    }
} PriceNode;


void update(avl_tree_node<Record> * node){
    auto max_price = node->value;
    if(node->left != nullptr) max_price = node->left->_max.price < max_price.price ? max_price : node->left->_max;
    if(node->right != nullptr) max_price = node->right->_max.price < max_price.price ? max_price : node->right->_max;
    node->_max = max_price;
}

/****************************************************************************
       F  I  N  A  L      D  A  T  A      S  T  R  U  C  T  U  R  E
****************************************************************************/

/**------------------------- Question 2 ----------------------------------**/

typedef struct DataStructure {
    /*-------------------- fields from question 2 --------------------------------*/
    avl_tree_node<Record> ** month_hits_subtrees = nullptr;
    int amount_of_left_subtrees = 0;
    int amount_of_subtrees = 0;

    /*-------------------- fields and functions from question 1 -------------------*/
    avl_tree<Record> tree1{&update};
    Record max_price = {-1, -1, ""};
    int last_serial_number = 1;

    DataStructure() = default;
    ~DataStructure() = default;

    void Init(){
        max_price = {-1, -1, ""};
    }

    void Insert(int price, std::string name){
        Record record = {last_serial_number++, price, name};
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
        if(max_price.serial_number == -1)
            std::cout << "No elements in the data structure, so default max_price is returned." << std::endl;
        return this->max_price;
    }

    /*-------------------- functions from question 2 ------------------------------*/
    void Pick_Month_Hits(int i, int j){
        /*
         * Description:
         *      The function finds the lca of the Record i, and the Record j, and inserts all the nodes in the path from the
         *      lca to the left node in which we turned right and vice versa.
         *      This helps the function Show_Month_Hits() to print out the correct subtrees of these nodes.
         *      Time Complexity: O(log n).
         *      Proof:
         *          getting the lca as described in the avl_tree implementation is only travelling through at most 2 search
         *          paths, and in an avl tree this is O(log n). iterating over the paths from the lca to both nodes is also
         *          at most 2 * |search path| which is also O(log n). Overall, this sums up to be O(log n).
         */
        if(i > j) {
            int t = i;
            i = j, j = t;
        }
        // keep in mind that the search is done only using the serial number
        Record dummy1 = {i, -1, ""}, dummy2 = {j, -1, ""};
        auto left_node = tree1.find(dummy1), right_node = tree1.find(dummy2);
        auto lca = tree1.lca(left_node, right_node);

        month_hits_subtrees = new avl_tree_node<Record> * [2 * tree1.root->height + 2];
        // inserting right path from lca to left_node
        auto it = lca->left;
        while(it != nullptr && it != left_node) {
            if(left_node->value < it->value){ // only left turned nodes
                month_hits_subtrees[amount_of_left_subtrees++] = it;
                it = it->left;
            } else it = it->right;
        }
        if(amount_of_left_subtrees == 0 || month_hits_subtrees[amount_of_left_subtrees-1] != left_node)
            month_hits_subtrees[amount_of_left_subtrees++] = left_node;

        // inserting left path from lca to right_node
        it = lca->right;
        amount_of_subtrees = amount_of_left_subtrees;
        while(it != nullptr && it != right_node) {
            if(it->value < right_node->value){ // only right turned nodes
                month_hits_subtrees[amount_of_subtrees++] = it;
                it = it->right;
            } else it = it->left;
        }
        if(amount_of_subtrees == amount_of_left_subtrees || month_hits_subtrees[amount_of_subtrees-1] != right_node)
            month_hits_subtrees[amount_of_subtrees++] = right_node;
        month_hits_subtrees[amount_of_subtrees] = lca;
    }

    void Show_Month_Hits() {
        /*
         * Description:
         *      The function uses the 'month_hits_subtrees' array built in 'Pick_Month_Hits()',
         *      it prints every right subtree of the nodes in the path from the lca to the left node, and vise versa.
         *      It uses inorder traversal to print the subtrees as shown in the lectures.
         *      Time Complexity: O(k), where k is the number of elements we need to print.
         */
        std::cout << "Month Hits: \n";
        for(int i = amount_of_left_subtrees-1; i >= 0; i--)
            std::cout << month_hits_subtrees[i]->value.name << " ", _inorder_print(month_hits_subtrees[i]->right);
        std::cout << month_hits_subtrees[amount_of_subtrees]->value.name << " ";
        for(int i = amount_of_left_subtrees; i < amount_of_subtrees; i++)
            _inorder_print(month_hits_subtrees[i]->left), std::cout << month_hits_subtrees[i]->value.name << " ";
    }

    void _inorder_print(avl_tree_node<Record> * node){
        if(node == nullptr) return;
        _inorder_print(node->left);
        std::cout << node->value.name << " ";
        _inorder_print(node->right);
    }

    void End_Month(){
        /*
         * Description:
         *      The function frees the memory of the array, and resets the sizes.
         *      Time Complexity: O(1), because freeing an array is O(1) (as shown in lectures).
         */
        delete month_hits_subtrees;
        amount_of_left_subtrees = 0, amount_of_subtrees = 0;
    }

} DataStructure;



