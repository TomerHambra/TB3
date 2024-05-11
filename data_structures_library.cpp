#include <iostream>

/****************************************************************************
                    I  N  F  O  R  M  A  T  I  O  N

        Lia Bercovitz - 328381926
        Tomer Hambra - 216634758

        Due Date - 7.5.24
        Submitted to Jonatan Sperber
****************************************************************************/



/****************************************************************************
                D  A  T  A      S  T  R  U  C  T  U  R  E  S
****************************************************************************/

/**------------------------- Helper Functions -----------------------------**/
// Time Complexity: O(1)
int max(int a, int b){ return a < b ? b : a; }


/**------------------------- Dynamic Array -------------------------------**/

template <typename T>
struct dynamic_array {
    int _size;
    int array_size;
    T *array;


    // Time Complexity: O(1)
    dynamic_array(int array_size=8) : _size(0), array_size(array_size), array(new T[array_size]) {};

    // Time Complexity: O(1)
    ~dynamic_array(){ delete [] this->array; }

    // Time Complexity:
    //      O(_size) worst case
    //      O(1) amortized
    void insert_last(T value){
        if(_size + 1 > array_size) {
            array_size = 2 * array_size;
            auto *temp = array;
            array = new T[array_size];
            for(int i = 0; i < _size; i++)
                array[i] = temp[i];
        } _size++;
        array[_size - 1] = value;
    }

    // Time Complexity: O(1)
    void remove_last(){
        if(_size == 0) return;
        return array[_size--];
    }

    // Time Complexity: O(1)
    T& operator[](int idx) {
        return array[idx];
    }

    // Time Complexity: O(1)
    int size() const { return _size; }

    // Time Complexity: O(_size)
    dynamic_array<T>& operator=(const dynamic_array<T>& other){
        // if function is called to set an array to be like itself
        if(this == &other)
            return *this;
        delete [] array;

        // copying 'other'
        _size = other._size;
        array_size = other.array_size;
        array = new T[other.array_size];
        if(other.array != nullptr)
            for(int i = 0; i < other._size; i++)
                array[i] = other[i];

        return *this;
    }

};


/**------------------------- AVL Tree ------------------------------------**/

template <typename T>
struct avl_tree_node {
    avl_tree_node<T> *left, *right;
    T value, _max;
    int count, height; // size of subtree and height
    void (*update)(avl_tree_node<T>*);


    static void none(avl_tree_node<T> *) {}

    // Time Complexity: O(1)
    avl_tree_node(T value, void (*update)(avl_tree_node<T> *) = &none) : value(value), left(nullptr), right(nullptr), count(1),
            update(update), height(1), _max({}) {};

    // Time Complexity: O(1)
    void update_values() {
        // function updates the node's values according to its children.
        this->count = (left != nullptr ? left->count : 0) + (right != nullptr ? right->count : 0) + 1;

        // keep in mind that in this course we defined a leaf's height to be 0.
        this->height = max(left != nullptr ? left->height : -1, right != 0 ? right->height : -1) + 1;

        update(this);
    }

    // Time Complexity: O(1)
    int balance_factor(){
        return (left != nullptr ? left->height : 0) - (right != nullptr ? right->height : 0);
    }

    // Time Complexity: O(1)
    avl_tree_node<T> *left_rotate(){
        avl_tree_node<T> * temp = right;
        right = right->left;
        temp->left = this;

        // we first update this' values because its temp's child now
        this->update_values();
        temp->update_values();
        return temp;
    }

    // Time Complexity: O(1)
    avl_tree_node<T> *right_rotate() {
        avl_tree_node<T> * temp = left;
        left = left->right;
        temp->right = this;

        // we first update this' values because its temp's child now
        this->update_values();
        temp->update_values();
        return temp;
    }
};


template <typename T>
struct avl_tree {
    /// NOTE: Keep in mind that unless specified otherwise, n is the amount of elements which is equivalent to _size.
    int _size;
    avl_tree_node<T> *root;
    bool (*comp)(T&, T&);
    void (*node_update)(avl_tree_node<T>*);


    // Time Complexity: O( T::operator< )
    static bool less(T& a, T& b) { return a < b; }

    // Time Complexity: O(1)
    avl_tree(void (*node_update)(avl_tree_node<T>*) = nullptr, bool (*comp)(T&, T&) = nullptr) : _size(0), root(nullptr),
            node_update(node_update), comp(comp) {
        if(comp == nullptr) this->comp = less;
        if(node_update == nullptr) node_update = &avl_tree_node<T>::none;
    };

    // Time Complexity: O(n)
    ~avl_tree() { this->clear_subtree(root); }

    // Time Complexity: O(n)
    void clear() { this->clear_subtree(root); }

    // Time Complexity: O(node.count)
    void clear_subtree(avl_tree_node<T> *node){
        if(node == nullptr) return;

        clear_subtree(node->left);
        clear_subtree(node->right);
        delete node;
    }

    // Time Complexity: O(log n)
    void insert(T key){ root = _insert(root, key); }

    // Time Complexity: O(log n)
    avl_tree_node<T>* _insert(avl_tree_node<T> *node, T key) {
        if(node == nullptr) return _size++, new avl_tree_node<T>(key, node_update);

        // deciding the direction to go down in.
        if(comp(key, node->value)) node->left = _insert(node->left, key);
        else if (comp(node->value, key)) node->right = _insert(node->right, key);
        else return node;

        // updating the node's values recursively through the search path and getting the balance factor.
        node->update_values();
        int bf = node->balance_factor();

        // dealing with each case of balancing the search path.
        if(bf > 1 && comp(key, node->left->value)) return node->right_rotate();
        if(bf > 1 && comp(node->left->value, key)) return node->left = node->left->left_rotate(), node->right_rotate();
        if(bf < -1 && comp(key, node->right->value)) return node->right = node->right->right_rotate(), node->left_rotate();
        if(bf < -1 && comp(node->right->value, key)) return node->left_rotate();

        return node;
    }

    // Time Complexity: O(log n)
    avl_tree_node<T>* find(T key) {
        return _find(root, key);
    }

    // Time Complexity: O(log n)
    avl_tree_node<T>* _find(avl_tree_node<T> * node, T key) {
        if(node == nullptr) return nullptr;

        if(comp(key, node->value)) node->left = _find(node->left, key);
        else if (comp(node->value, key)) node->right = _find(node->right, key);
        else return node;
    }

    // Time Complexity: O(log n)
    void remove(T key){ root = _delete(root, key); }

    // Time Complexity: O(log n)
    avl_tree_node<T>* _delete(avl_tree_node<T> *node, T key) {
        if(node == nullptr) return node;

        // locating the node's search path, if found delete it (free the memory).
        if(comp(key, node->value)) node->left = _delete(node->left, key);
        else if(comp(node->value, key)) node->right = _delete(node->right, key);
        else {
            if(node->left == nullptr || node->right == nullptr) {
                avl_tree_node<T> *temp = node->left != nullptr ? node->left : node->right;
                if (temp == nullptr) temp = node, node = nullptr;
                else *node = *temp; // copying the fields of temp, this deals with the case where we pull a child up.
                delete temp;
                _size--;
            }else {
                avl_tree_node<T> *temp = min_node(node->right);
                root->value = temp->value; // copying just the key, not the other fields.
                root->right = _delete(node->right, temp->value);
            }
        }
        if(node == nullptr) return node;

        // updating the values and calculating the balance factor bf.
        node->update_values();
        int bf = node->balance_factor();

        // dealing with the cases of balancing like in the lectures.
        if(bf > 1 && node->left->balance_factor() >= 0) return node->right_rotate();
        if(bf > 1 && node->left->balance_factor() < 0) return node->left = node->left->left_rotate(), node->right_rotate();
        if(bf < -1 && node->right->balance_factor() > 0) return node->right = node->right->right_rotate(), node->left_rotate();
        if(bf < -1 && node->right->balance_factor() <= 0) return node->left_rotate();
    }

    // Time Complexity: O(log n) where n is node.count or the number of elements in node's subtree
    avl_tree_node<T> * min_node(avl_tree_node<T> *node){
        if(node == nullptr) return node;
        // returns the minimum value node in node's subtree.
        while(node->left != nullptr) node = node->left;
        return node;
    }

    // Time Complexity: O(log n)
    avl_tree_node<T> * min_node(){
        // returns the minimum value node in tree.
        auto node = root;
        if(node == nullptr) return node;
        while(node->left != nullptr) node = node->left;
        return node;
    }

    // Time Complexity: O(log n) where n is node.count or the number of elements in node's subtree
    avl_tree_node<T> * max_node(avl_tree_node<T> *node){
        if(node == nullptr) return node;
        // returns the maximum value node in node's subtree.
        while(node->right != nullptr) node = node->right;
        return node;
    }

    // Time Complexity: O(log n)
    avl_tree_node<T> * max_node(){
        // returns the maximum value node in tree.
        auto node = root;
        if(node == nullptr) return node;
        while(node->right != nullptr) node = node->right;
        return node;
    }

    // Time Complexity: O(log n)
    avl_tree_node<T> *lca(avl_tree_node<T> * node1, avl_tree_node<T> * node2){
        // return the lowest common ancestor of node1 and node2
        if(node1 == nullptr || node2 == nullptr) return (node1 ? node1 : node2);
        if(node1 == node2) return node1;
        avl_tree_node<T> * t = root;
        while(comp(t->value, node1->value) == comp(t->value, node2->value))
            t = (comp(t->value, node1->value) ? t->right : t->left);
        return t;
    }

    // Time Complexity: O(log n)
    avl_tree_node<T> *node_by_rank(int r){
        if(_size == 0 || r < 1 || r > _size) return nullptr;
        return _get_rank(root, r);
    }

    // Time Complexity: O(log n)
    avl_tree_node<T> *_get_rank(avl_tree_node<T> *node, int r){
        if(node == nullptr) return nullptr;
        if(node->left == nullptr) {
            if(r == 1) return node;
            return _get_rank(node->right, r - 1);
        }
        if(r == node->left->count + 1) return node;
        if(r < node->left->count + 1) return _get_rank(node->left, r - 1);
        return _get_rank(node->right, r - node->left->count - 1);
    }
    /// TODO:
    ///    - Split for avl trees.

    // Time Complexity: O(1)
    int size() const { return _size; }
};




