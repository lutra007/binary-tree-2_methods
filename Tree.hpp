#include <iostream>
using namespace std;

struct Node {
  int x;
  Node *left;
  Node *right;
};

namespace ariel {
class Tree {
public:  
  ~Tree();
  void insert(int key);
  bool contains(int key);
  void remove(int key);
  int parent(int key);
  int left(int key);
  int right(int key);
  void print();
  int root();
  int size();
  
private:
  Node *my_tree = NULL;
  int tree_size = 0;
  
  void insert(int x, Node *&MyTree);
  bool search(int key,Node *&my_tree);
  void remove(int x, Node *&MyTree);
  int parent(int key, int par, Node *&my_tree);
  int leaf(int key, bool check_side, Node *&my_tree);
  void print(Node *&my_tree);
  int bring_left(Node *&MyTree);
  bool empty(Node *&MyTree);
  int root(Node *&my_tree);
  void del(Node *&my_tree);
};  
  
Tree::~Tree() {
    del(my_tree);
  }
  
void Tree::print() {
    print(my_tree);
    cout << "\n";
  }
  
void Tree::insert(int x) {
    insert(x,my_tree);
    tree_size++;
  }
  
int Tree::root() {
    return root(my_tree);
  }
  
int Tree::size() {
    return tree_size;
  }
  
bool Tree::contains(int key) {
    return search(key,my_tree);
  }
  
void Tree::remove(int x) {
    bool present = search(x,my_tree);
    if (present) {
      remove(x,my_tree);
      tree_size--;
    }
    else {
      string error = to_string(x) + " doesn't exist!";
      throw error;
    }
  }
  
int Tree::parent(int key) {
    bool present = search(key,my_tree);
    if (present) {
      int r = root(my_tree);
      if (key == r) {
        string error = "No parent for root!";
        throw error;
      }
      else {
	return parent(key,r,my_tree);
      }
    }
    else {
      string error = to_string(key) + " was not found!";
      throw error;
    }
  }
  
int Tree::left(int key) {
    bool present = search(key,my_tree);
    if (present) {
      bool left_side = true;
      return leaf(key,left_side,my_tree);
    }
    else {
      string error = to_string(key) + " was not found!";
      throw error;
    }
  }
  
int Tree::right(int key) {
    bool present = search(key,my_tree);
    if (present) {
      bool left_side = false;
      return leaf(key,left_side,my_tree);
    }
    else {
      string error = to_string(key) + " was not found!";
      throw error;
    }
  }
  

void Tree::print(Node *&my_tree) {
    if (my_tree != NULL) {
      print(my_tree->left);
      cout << my_tree->x << " ";
      print(my_tree->right);
    }
  }
  
bool Tree::search(int key,Node *&my_tree) {
    if (my_tree != NULL) {
      if (my_tree->x) {
        if (my_tree->x == key) {
	  return true;
        }
        else if (my_tree->x > key) {
	  return search(key,my_tree->left);
        }
        else if (my_tree->x < key) {
	  return search(key,my_tree->right);
        }
      }
      else {
        return false;
      }
    }
    else {
      return false;
    } 
  }
  
int Tree::parent(int key, int par, Node *&my_tree) {
    if (my_tree->x == key) {
	return par;
      }
      else if (my_tree->x > key) {
	return parent(key,my_tree->x,my_tree->left);
      }
      else if (my_tree->x < key) {
	return parent(key,my_tree->x,my_tree->right);
      }
  }
  
int Tree::leaf(int key, bool check_side, Node *&my_tree) {
    if (my_tree->x == key) {
	if (check_side) {
	  bool lside_is_empty = empty(my_tree->left);
	  if (lside_is_empty) {
	    string error = to_string(key) + " doesn't have a left child!";
	    throw error;
	  }
	  else {
	    return my_tree->left->x;
	  }
	}
	else {
	  bool rside_is_empty = empty(my_tree->right);
	  if (rside_is_empty) {
	    string error = to_string(key) + " doesn't have a right child!";
	    throw error;
	  }
	  else {
	    return my_tree->right->x;
	  }
	}
      }
      else if (my_tree->x > key) {
	return leaf(key,check_side,my_tree->left);
      }
      else if (my_tree->x < key) {
	return leaf(key,check_side,my_tree->right);
      }
  }
  
void Tree::del(Node *&my_tree) {
    if (my_tree != NULL) {
      del(my_tree->left);
      del(my_tree->right);
      delete my_tree;
      my_tree = NULL;
    }
  }
  
void Tree::insert(int x, Node *&MyTree) {
    if (NULL == MyTree)
    {
      MyTree = new Node;
      MyTree->x = x;
      MyTree->left = MyTree->right = NULL;
    }
  
    else if (x < MyTree->x) {
      if (MyTree->left != NULL) {
        insert(x, MyTree->left);
      }
      else {
        MyTree->left = new Node;
        MyTree->left->left = MyTree->left->right = NULL;
        MyTree->left->x = x;
      }
    }
    else if (x > MyTree->x) {
      if (MyTree->right != NULL) {
        insert(x, MyTree->right);
      }
      else {
        MyTree->right = new Node;
        MyTree->right->left = MyTree->right->right = NULL;
        MyTree->right->x = x;
      }
    }
    else {
      string error = to_string(x) + " already exists";
      throw error;
    }
  }
  
void Tree::remove(int x, Node *&MyTree) {
    if (x == MyTree->x) { 
        bool lside_is_empty = empty(MyTree->left);
	bool rside_is_empty = empty(MyTree->right);
	
	if (lside_is_empty && rside_is_empty) {
	  del(MyTree);
	}
	else if (lside_is_empty) {
	  MyTree = MyTree->right;
	}
	else if (rside_is_empty) {
	  MyTree = MyTree->left;
	}
	else {
	  MyTree->x = bring_left(MyTree->right);
	}
    }
    else if (x > MyTree->x) {
        remove(x, MyTree->right);
    }
    else if (x < MyTree->x) {
        remove(x, MyTree->left);
    }
  }

//I have a memory leak somewhere here
int Tree::bring_left(Node *&MyTree) {
    bool lside_is_empty = empty(MyTree->left);
    if (lside_is_empty) {
      int save = MyTree->x;
      MyTree = MyTree->right;
      return save;
    }
    else {
      return bring_left(MyTree->left);
    }
  }
   
bool Tree::empty(Node *&MyTree) {
    if (MyTree != NULL) {
      return false;
    }
    else {
      return true;
    }
  } 
  
int Tree::root(Node *&my_tree) {
    if (my_tree != NULL) {
      return my_tree->x;
    }
    else {
      string error = "Empty tree!";
      throw error;
    }
  }
}