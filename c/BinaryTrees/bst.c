#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef enum {
  FALSE = 0,
  TRUE = 1
} bool;

struct BST;

// Implementation of binary search tree
typedef struct BST {
  int key;
  void* val;
  struct BST* left;
  struct BST* right;
  struct BST* parent;
} BST;

// Binary Search Tree Constructor
BST* new_Node(int key, void* val, BST* parent) {
  BST* retval = malloc(sizeof *retval);
  retval->key = key;
  retval->val = val; // If value is null, then node is empty
  retval->left = NULL;
  retval->right = NULL;
  retval->parent = parent;
  return retval;
}

BST* new_BST() {
  return new_Node(0, NULL, NULL);
}

// Recursively frees all objects referenced by pointers of BST
// if subtree returns true, then it should be freed
// if subtree returns false, then it shouldn't be freed
bool deleteBST(BST* this) {
  if (this == NULL) {
    // This node was NOT allocated with malloc, so it shouldn't be free()'d
    return FALSE;
  }
  else {
    // Free subtrees if they were allocated with malloc
    if (deleteBST(this->left) == TRUE) {
      free(this->left);
      this->left = NULL;
    }
    if (deleteBST(this->right) == TRUE) {
      free(this->right);
      this->right = NULL;
    }

    // Free current tree
    free(this->val);
    this->val = NULL;
    return TRUE;
  }
}

// Adds node to Tree, returns pointer to current modified tree
BST* addNode(BST* this, int key, void* val) {
  if (val == NULL) {
    return NULL;
  }

  // Tree is empty, has no head
  if (this->val == NULL) { 
    this->key = key;
    this->val = val;
    this->parent = NULL;
    return this;
  }
  // Tree has elements
  else {
    // If the current node has the same key, modify the value.
    if (key == this->key) {
      this->val = val;
      return this;
    }
    // Insert into left subtree
    else if (key < this->key) {
      // If we've reached the end
      if (this->left == NULL) {
        this->left = new_Node(key, val, this);
        return this->left;
      }
      // Or we still have to go more left
      else {
        return addNode(this->left, key, val);
      }
    }
    // Insert into right subtree
    else if (key > this->key) {
      // We've reached the end
      if (this->right == NULL) {
        this->right = new_Node(key, val, this);
        return this->right;
      }
      // Or we still have to go
      else {
        return addNode(this->right, key, val);
      }
    }
    else {
      return NULL;
    }
  }
}

void* getVal(BST* this, int key) {
  if (this == NULL) {
    return NULL;
  }

  if (key == this->key) {
    return this->val;
  }
  else if (key < this->key) {
    return getVal(this->left, key);
  }
  else if (key > this->key) {
    return getVal(this->right, key);
  }
  else {
    return NULL;
  }
}

// Performs inorder traversal on binary tree, prints all elements
void printBST(BST* this, const char* (*toString)(void* object)) {
  if (this->left != NULL)
    printBST(this->left, toString);

  printf("%d/%s ", this->key, (*toString)(this->val));

  if (this->right != NULL)
    printBST(this->right, toString);
}

// Function to convert values from a void* pointer into a C-string
const char* toCString(void* object) {
  return (const char*) object;
}

int main() {
  BST* tree = new_BST();

  char* one = malloc(sizeof(*one) * 4);
  char* two = malloc(sizeof(*one) * 4);
  char* three = malloc(sizeof(*one) * 6);
  char* four = malloc(sizeof(*one) * 5);
  char* five = malloc(sizeof(*one) * 5);
  strcpy(one, "one");
  strcpy(two, "two");
  strcpy(three, "three");
  strcpy(four, "four");
  strcpy(five, "five");

  addNode(tree, 3, three);
  addNode(tree, 1, one);
  addNode(tree, 5, five);
  addNode(tree, 4, four);
  //printf("%d\n%d\n%d ", tree->key, tree->left->key, tree->right->key);
  printBST(tree, toCString);
  printf("\n");

  printf("Retrieving value stored with key 4... %s!\n",
         toCString(getVal(tree, 4)));

  deleteBST(tree);
  //free(tree);

  return 0;
}
