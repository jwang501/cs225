/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    Node* temp = t;
    t = t->right;
    temp->right = t->left;
    t->left = temp;
    if (heightOrNeg1(temp->left) > heightOrNeg1(temp->right)) {
      temp->height = 1 + heightOrNeg1(temp->left);
    } else {
      temp->height = 1 +  heightOrNeg1(temp->right);
    }
    if (heightOrNeg1(t->left) > heightOrNeg1(t->right)) {
      t->height = 1 + heightOrNeg1(t->left);
    } else {
      t->height = 1 +  heightOrNeg1(t->right);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    Node* temp = t;
    t = t->left;
    temp->left = t->right;
    t->right = temp;
    if (heightOrNeg1(temp->left) > heightOrNeg1(temp->right)) {
      temp->height = 1 + heightOrNeg1(temp->left);
    } else {
      temp->height = 1 + heightOrNeg1(temp->right);
    }
    if (heightOrNeg1(t->left) > heightOrNeg1(t->right)) {
      t->height = 1 + heightOrNeg1(t->left);
    } else {
      t->height = 1 + heightOrNeg1(t->right);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    if (subtree == NULL) {
      return;
    }
    if (heightOrNeg1(subtree->left) - heightOrNeg1(subtree->right) > 1) {
      if (heightOrNeg1(subtree->left->left) - heightOrNeg1(subtree->left->right) > 0) {
        rotateRight(subtree);
      } else {
        rotateLeftRight(subtree);
      }
    } else if (heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left) > 1) {
      if (heightOrNeg1(subtree->right->left) - heightOrNeg1(subtree->right->right) > 0) {
        rotateRightLeft(subtree);
      } else {
        rotateLeft(subtree);
      }
    }
    if (heightOrNeg1(subtree->left) > heightOrNeg1(subtree->right)) {
      subtree->height = 1 + heightOrNeg1(subtree->left);
    } else {
      subtree->height = 1 + heightOrNeg1(subtree->right);
    }
    return;
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    if (subtree == NULL) {
      Node* toInsert = new Node(key,value);
      subtree = toInsert;
    }
    if (subtree->key > key) {
      insert(subtree->left,key,value);
      if (heightOrNeg1(subtree->left)> heightOrNeg1(subtree->right)) {
        subtree->height++;
      }
      rebalance(subtree);
    }
    if (subtree->key < key) {
      insert(subtree->right,key,value);
      if (heightOrNeg1(subtree->right) > heightOrNeg1(subtree->left)) {
        subtree->height++;
      }
      rebalance(subtree);
    }
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{   return;
    if (subtree == NULL)
        return;
    if (key < subtree->key) {
        remove(subtree->left,key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        remove(subtree->right,key);
        rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
          Node* temp = subtree;
          subtree = NULL;
          delete temp;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            Node* current = subtree->left;
            while(current->right) {
              current = current->right;
            }
            swap(subtree,current);
            Node* temp = current;
            current = current->left;
            delete temp;
        } else {
          if (subtree->left == NULL) {
            swap(subtree,subtree->right);
            Node* temp = subtree->right;
            subtree->right = NULL;
            delete temp;
          } else {
            swap(subtree,subtree->left);
            Node* temp = subtree->left;
            subtree->left = NULL;
            delete temp;
          }
          rebalance(subtree);
        }
    }
}
