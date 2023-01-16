#ifndef BST_H_
#define BST_H_

#include <memory>
#include <string>
#include <vector>

// Implementation of binary search tree
template<typename K, class V>
class BST {
private:
  K key;
  V val;
  std::shared_ptr< BST<K, V> > left;
  std::shared_ptr< BST<K, V> > right;
  std::weak_ptr< BST<K, V> > parent;

public:
  struct KeyVal {
    K key;
    V val;
  };

public:
  BST(K key, V val, BST<K,V> parent);
  ~BST();
  std::shared_ptr< BST<K, V> > addNode(K key, V val);
  V getVal(int key);

  std::vector<KeyVal> inOrder();
  std::vector<KeyVal> preOrder();
  std::vector<KeyVal> postOrder();
  std::vector<KeyVal> breadthFirst();
  std::vector<KeyVal> depthFirst();
};

#endif // BST_H_
