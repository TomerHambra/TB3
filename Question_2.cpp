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


typedef struct PriceNode {
    int price;
    avl_tree<Record> * records_tree;

    PriceNode(int price) : price(price), records_tree(nullptr) {
        records_tree = new avl_tree<Record>();
    };

    ~PriceNode(){
        delete records_tree;
    }

    bool operator<(PriceNode& other){
        return price < other.price;
    }
} PriceNode;



/****************************************************************************
       F  I  N  A  L      D  A  T  A      S  T  R  U  C  T  U  R  E
****************************************************************************/

/**------------------------- Question 2 ----------------------------------**/

typedef struct DataStructure {
    /*-------------------- fields from question 2 --------------------------------*/
    avl_tree_node<Record> ** month_hits_subtrees = nullptr;
    int amount_of_left_subtrees = 0;
    int amount_of_subtrees = 0;

    /*-------------------- fields and function from question 1 -------------------*/
    avl_tree<Record> tree1;
    avl_tree<PriceNode> tree2;
    Record max_price = {-1, -1, ""};
    int next_serial_number = 1;


    DataStructure() = default;
    ~DataStructure() = default;

    void Init(){
        /*
         * Description:
         *      The function initializes the fields.
         *      Time Complexity: O(1).
         */
        max_price = {-1, -1, ""};
        next_serial_number = 1;
    }

    void Insert(int price, std::string name){
        /*
         * Description:
         *      The function creates a record object, increments the 'next_serial_number' parameter, and then inserts
         *      it to tree 1. Then it creates a priceNode object and inserts the record object to the records tree in that
         *      node, and inserts the priceNode object to tree2. Lastly, the function updates the 'max_price' field
         *      accordingly.
         *      Time Complexity: O(log n).
         */
        Record record = {next_serial_number++, price, name};
        tree1.insert(record);

        PriceNode priceNode(price);
        priceNode.records_tree->insert(record);
        tree2.insert(priceNode);

        if(price > max_price.price) max_price = record;
    }

    void Delete(int number){
        /*
         * Description:
         *      The function finds the record with serial number 'number', deletes it from tree1, and from the tree inside
         *      the record's price node in tree2, and if that inner tree is now empty, it deletes the price node.
         *      It also updates the max price record if we deleted the current max price record.
         *      Time Complexity: O(log n).
         */
        // keep in mind that the search is done only using the serial number
        Record dummy = {number, -1, ""};
        auto temp = tree1.find(dummy);
        if(temp == nullptr) return; // no need to delete something that is not in the trees.
        Record record = temp->value;

        tree1.remove(record);
        PriceNode dummy2(record.price);
        auto temp2 = tree2.find(dummy2);
        if(temp2 == nullptr) { return std::cout << "Shouldn't happen, something is wrong..." << std::endl, void(); }
        PriceNode priceNode = temp2->value;
        priceNode.records_tree->remove(record);
        if(priceNode.records_tree->size() == 0) tree2.remove(priceNode); // if we deleted the last record with this price

        if(tree2.size() == 0) return max_price =  {-1, -1, ""}, void();
        if(max_price.serial_number != record.serial_number) return; // if we deleted a record which is not the current max
        auto maxNode = tree2.max_node();
        if(maxNode == nullptr) { return std::cout << "Shouldn't happen too, something is wrong..." << std::endl, void(); }
        auto root = maxNode->value.records_tree->root;
        if(root != nullptr){
            // since we are guaranteed to have deleted the current max price, the max returned by max node is for sure
            // the correct one, and we only need to get one record which has the max price, so wlog we pick the root record.
            max_price = root->value;
        }
    }

    Record Max_Price() {
        /*
         * Description:
         *      The function returns the maintained 'max_price' field.
         *      Time Complexity: O(1).
         */
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
        if(j > i) {
            int t = i;
            i = j, j = t;
        }
        // keep in mind that the search is done only using the serial number
        Record dummy1 = {i, -1, ""}, dummy2 = {j, -1, ""};
        auto left_node = tree1.find(dummy1), right_node = tree1.find(dummy2);
        auto lca = tree1.lca(left_node, right_node);


        month_hits_subtrees = new avl_tree_node<Record> * [2 * tree1.root->height];
        // inserting right path from lca to left_node
        auto it = lca;
        while(it != left_node) {
            if(it->value < left_node->value){ // only right turned nodes
                it = it->right;
                month_hits_subtrees[amount_of_left_subtrees++] = it;
            } else it = it->left;
        }
        if(month_hits_subtrees[amount_of_left_subtrees-1] != left_node) month_hits_subtrees[amount_of_left_subtrees++] = left_node;

        // inserting left path from lca to right_node
        it = lca;
        amount_of_subtrees = amount_of_left_subtrees;
        while(it != right_node) {
            if(right_node->value < it->value){ // only left turned nodes
                it = it->left;
                month_hits_subtrees[amount_of_left_subtrees++] = it;
            } else it = it->right;
        }
        if(month_hits_subtrees[amount_of_left_subtrees-1] != right_node) month_hits_subtrees[amount_of_subtrees++] = right_node;

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
            std::cout << month_hits_subtrees[i]->value.name << " ", inorder_print(month_hits_subtrees[i]->right);
        for(int i = amount_of_subtrees-1; i >= amount_of_subtrees; i--)
            std::cout << month_hits_subtrees[i]->value.name << " ", inorder_print(month_hits_subtrees[i]->left);
    }

    void inorder_print(avl_tree_node<Record> * node){
        if(node == nullptr) return;
        inorder_print(node->left);
        std::cout << node->value.name << " ";
        inorder_print(node->right);
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



