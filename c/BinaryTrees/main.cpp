#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include <cstdlib>
#include <ctime>

// To make BSTs more extendable and searchable, all things have a key separate from their value.
template<typename K, typename V>
class BinaryTree
{
private:
  struct Node
  {
    const K key;
    const V val;
    int level;
    std::weak_ptr<Node> parent;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    Node(K key, V val, std::shared_ptr<Node> parent, int level)
    :key(key), val(val), parent(parent), level(level), left(nullptr), right(nullptr)
    {}
  };

public:
  std::shared_ptr<Node> root;

public:
  BinaryTree()
  :root(nullptr)
  {
    // Will add next on add command
  }

  void add(K newKey, V newVal)
  {
    // Because the BST is initialized without a root, we need to check if the root is empty on every add() call.
    if(root == nullptr)
    {
      root.reset(new  Node(
                            newKey,
                            newVal,
                            std::shared_ptr<Node>(nullptr),
                            0
                          )
                );
      return;
    }

    // Traversing down the tree
    std::shared_ptr<Node> pCurrentNode = root;
    while(true)
    {
      // Left Node
      if(newKey < pCurrentNode->key)
      {
        if(pCurrentNode->left == nullptr)
        {
          pCurrentNode->left.reset(new Node(newKey, newVal, pCurrentNode, pCurrentNode->level + 1));
          break;
        }
        else
        {
          pCurrentNode = pCurrentNode->left;
          continue;
        }
      }
      // Right Node
      else if(newKey > pCurrentNode->key)
      {
        if(pCurrentNode->right == nullptr)
        {
          pCurrentNode->right.reset(new Node(newKey, newVal, pCurrentNode, pCurrentNode->level + 1));
          break;
        }
        else
        {
          pCurrentNode = pCurrentNode->right;
          continue;
        }
      }
      else
      {
        std::string errMesg = "Tried to create duplicate element in Binary Tree with key " + std::to_string(newKey) + " and value " + std::to_string(newVal);
        throw std::out_of_range(errMesg);
      }
    }
  }
  void add(K newKey)
  {
    this->add(newKey, (V)newKey);
  }

  std::pair<K, V> search(K wantedKey)
  {
    std::shared_ptr<Node> pCurrentNode(root);
    while(true)
    {
//      std::cout << pCurrentNode->key << std::endl;
      if(pCurrentNode == nullptr)
      {
        std::string errMesg = "Requested non-existent key " + std::to_string(wantedKey);
        throw std::out_of_range(errMesg);
        return std::pair<K, V>((K)0, (V)0);
      }
      else if(pCurrentNode->key == wantedKey)
      {
        return std::pair<K, V>(pCurrentNode->key, pCurrentNode->val);
      }
      else
      {
        if(wantedKey < pCurrentNode->key)
        {
          pCurrentNode = pCurrentNode->left;
        }
        else if(wantedKey < pCurrentNode->key)
        {
          pCurrentNode = pCurrentNode->right;
        }
      }
    }
  }

// This function is for printing out the binary tree, honestly only useful for certain circumstances
  void printOut(int textWidth = 6)
  {
/*    std::cout << std::setw(textWidth);
    std::cout << std::right;*/
    std::vector< std::vector< std::shared_ptr< Node> > > levelMap;
    std::vector<bool> levelIsPopulated;
    std::shared_ptr<Node> pCurrentNode(root);
    // Go to the leftmost point possible, then after reaching nullptr, go up one and right.
    // If none are found on the right, go up one and go to the right.
    // Make sure never to go to the left after going up, because going up meanst that you've already been to the left
    while(true)
    {
      while(pCurrentNode != nullptr)
      {
        pCurrentNode = pCurrentNode->left;
      }
      // Once you've gone as left as you can, print the leftmost node out
      std::cout << pCurrentNode->key << ": " << pCurrentNode->val << " | ";
      pCurrentNode = pCurrentNode->parent;
      pCurrentNode = pCurrentNode->right;
    }
    return;
  }
};

int main()
{
  srand(time(NULL));

  BinaryTree<int, int> bt;
  int nuNum;
  for(int i = 0; i < 100; i++)
  {
    nuNum = rand() % 100;
    try
    {
      bt.add(nuNum);
    }
    catch(std::out_of_range)
    {
      continue;
    }
  }
  
  //
  bt.printOut();
}
