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

/**------------------------- Question 1 ----------------------------------**/

typedef struct DataStructure {
    /*
     * Solution:
     *      We will maintain an AVL tree of Records, which holds a serial number, a price and a name.
     *      The tree will be ordered by each node's serial number. - tree1
     *      We will also maintain another AVL tree of PriceNode, which is a struct that holds a price of a record,
     *      and an AVL tree in itself where each node holds a Record struct. The big AVL tree is ordered by
     *      price, and each node's AVL tree is ordered by the serial number. -tree2
     *      The Max_Price() method will be maintained via a field called 'max_price', which is updated using comparisons
     *      in Inserts, and using tree2 in Deletes.
     */

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

} DataStructure;