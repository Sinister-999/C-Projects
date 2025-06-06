/***
* Jestin Baath
* jsbaath
* 2024 Fall CSE101 PA7
* Dictionary.cpp
* Dictionary ADT
***/
#include <iostream>
#include "Dictionary.h"


Dictionary::Node::Node(keyType k, valType v) {
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = BLACK;
}

Dictionary::Dictionary() {
    this->nil = new Node("",0);
    this->nil->left = this->nil->right = this->nil->parent = this->nil;
    this->root = nil;
    this->current = root;
    this->num_pairs = 0;
}

//Helper Functions
void Dictionary::setCursor(keyType K){
    if (this->contains(K)) {
        this->begin();
        while (this->currentKey() != K) {
            this->next();
        }
    }
}

void Dictionary::inOrderString(std::string &s, Dictionary::Node *R) const {
    if (R != nil) {
        inOrderString(s, R->left);
        s += R->key + " : " + std::to_string(R->val) + "\n";
        inOrderString(s, R->right);
    }
}

void Dictionary::preOrderString(std::string &s, Dictionary::Node *R) const {
    if (R != nil) {
        s += R->key + "\n";
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }


}

Dictionary::Node* Dictionary::search(Dictionary::Node *R, keyType k) const {
    if (R == nullptr || R == this->nil){
        return R;
    } else if(R->key == k){
        return R;
    } else if (k < R->key){
        return search(R->left, k);
    } else{
        return search(R->right, k);
    }
}

Dictionary::Node* Dictionary::findMax(Dictionary::Node *R) {
    while (R->right != nil) {
        R = R->right;
    }
    return R;
}

void Dictionary::preOrderInsert(Node* R, Node* Nil) {
    if (R != Nil) {
        // Insert the current node into the new tree
        this->setValue(R->key, R->val);

        // Recur to the left and right subtrees
        preOrderInsert(R->left, Nil);
        preOrderInsert(R->right, Nil);
    }
}

Dictionary::Dictionary(const Dictionary &D) {
    this->nil = new Node("", 0);
    this->root = this->nil;
    this->current = this->nil;
    this->num_pairs = 0;

    if (D.root != D.nil) {
        preOrderInsert(D.root, D.nil);
    }
}

Dictionary::~Dictionary() {
    this->clear();
    delete this->nil;
}

//Access Func
int Dictionary::size() const {
    return this->num_pairs;
}

bool Dictionary::contains(keyType k) const {
    if (search(this->root, k) == this->nil){
        return false;
    } else{
        return true;
    }
}

valType& Dictionary::getValue(keyType k) const {
    if (this->contains(k)){
        Node* temp = search(this->root, k);
        return temp->val;
    }
}

bool Dictionary::hasCurrent() const {
    if(this->current == this->nil){
        return false;
    } else{
        return true;
    }
}

keyType Dictionary::currentKey() const {
    if (this->hasCurrent()){
        return this->current->key;
    } else{
        throw std::logic_error("currentVal(): No current element.");
    }
}

valType& Dictionary::currentVal() const {
    if (this->hasCurrent()){
        return this->current->val;
    } else{
        throw std::logic_error("currentVal(): No current element.");
    }
}

void Dictionary::clearHelper(Node* R) {
    if (R != nil) {
        clearHelper(R->left);
        clearHelper(R->right);
        delete R;
    }
}

// Manipulation
void Dictionary::clear() {
    clearHelper(root);
    root = nil;
    current = nil;
    num_pairs = 0;
}

void Dictionary::setValue(keyType k, valType v) {
    if (this->contains(k)){
        Node* temp = this->current;
        temp = this->root;
        while (temp->key != k && temp != nil){
            if (k < temp->key){
                temp = temp->left;
            } else {
                temp = temp->right;
            }
        }
        temp->val = v;
    } else if (this->num_pairs == 0){
        Node* temp = new Node(k, v);
        temp->parent = this->nil;
        this->current = temp;
        temp->left = temp->right = this->nil;
        this->root = temp;
        this->num_pairs++;
    } else {
        Node *temp = this->root;
        while (temp != nil){
            if (k < temp->key){
                if (temp->left == this->nil){
                    break;
                }
                temp= temp->left;
            } else {
                if (temp->right == this->nil){
                    break;
                }
                temp = temp->right;
            }
        }
        Node* temp1 = new Node(k, v);
        temp1->parent = temp;
        temp1->left = temp1->right = this->nil;
        if (k < temp->key){
            temp->left = temp1;
        } else {
            temp->right = temp1;
        }
        this->num_pairs++;

    }
}

void Dictionary::remove(keyType k) {
    if (this->contains(k)) {
        bool reset = false;
        keyType K = this->currentKey();
        if (this->hasCurrent()) {
            reset = true;
        }
        this->current = this->root;
        while (this->current->key != k && this->current != nil){
            if (k < this->current->key){
                this->current = this->current->left;
            } else {
                this->current = this->current->right;
            }
        }
        if (this->current->left == this->nil && this->current->right == this->nil){
            if (this->current == this->root){
                this->root = this->nil;
                delete this->current;
                this->num_pairs--;
            } else if (this->current->key < this->current->parent->key){
                this->current->parent->left = this->nil;
                delete this->current;
                this->current = nil;
                this->num_pairs--;
            } else {
                this->current->parent->right = this->nil;
                delete this->current;
                this->current = nil;
                this->num_pairs--;
            }
        } else if (this->current->right == this->nil && this->current->left != this->nil){
            if (this->current == this->root){
                this->root = this->current->left;
                this->current->left->parent = this->nil;
                delete this->current;
                this->num_pairs--;
            } else if (this->current->key < this->current->parent->key){
                this->current->parent->left = this->current->left;
                this->current->left->parent = this->current->parent;
                delete this->current;
                this->num_pairs--;
            } else {
                this->current->parent->right = this->current->left;
                this->current->left->parent = this->current->parent;
                delete this->current;
                this->num_pairs--;
            }
        } else if (this->current->right != this->nil && this->current->left == this->nil){
            if (this->current == this->root){
                this->root = this->current->right;
                this->current->right->parent = this->nil;
                delete this->current;
                this->num_pairs--;
            } else if (this->current->key < this->current->parent->key){
                this->current->parent->left = this->current->right;
                this->current->right->parent = this->current->parent;
                delete this->current;
                this->num_pairs--;
            } else {
                this->current->parent->right = this->current->right;
                this->current->right->parent = this->current->parent;
                delete this->current;
                this->num_pairs--;
            }
        } else if (this->current->left != this->nil && this->current->right != this->nil) {
            Node *successor = this->current->right;
            while (successor->left != this->nil) {
                successor = successor->left;
            }
            this->current->key = successor->key;

            // Remove successor node (it will have at most one child)
            if (successor->right != this->nil) {
                if (successor == successor->parent->left) {
                    successor->parent->left = successor->right;
                } else {
                    successor->parent->right = successor->right;
                }
                successor->right->parent = successor->parent;
            } else {
                if (successor == successor->parent->left) {
                    successor->parent->left = this->nil;
                } else {
                    successor->parent->right = this->nil;
                }
            }

            delete successor;
            this->num_pairs--;
        }

        if (reset){
            this->setCursor(K);
        }
    }
}

void Dictionary::begin() {
    if (this->num_pairs > 0){
        this->current = this->root;
        while (this->current->left != nil){
            this->current = this->current->left;
        }
    }
}

void Dictionary::end() {
    if (this->num_pairs > 0){
        this->current = this->root;
        while (this->current->right != nil){
            this->current = this->current->right;
        }
    }
}

void Dictionary::next() {
    if (this->hasCurrent()) {
        if (this->current->right != nil) {
            this->current = this->current->right;
            while (this->current->left != nil) {
                this->current = this->current->left;
            }
        } else {
            Node* temp = this->current;
            while (temp->parent != this->nil && temp == temp->parent->right) {
                if (temp->parent == this->nil && temp == temp->parent->right){
                    this->current = this->nil;
                    return;
                }
                temp = temp->parent;
            }
            this->current = temp->parent;
        }
    }
}

void Dictionary::prev() {
    if (this->current->left != nil){
        this->current = this->current->left;
        while (this->current->right != nil){
            this->current = this->current->right;
        }
    } else {
        Node* temp = current;
        while (temp->parent != nil && temp == temp->parent->left){
            temp = temp->parent;
        }
        this->current = temp->parent;
    }
}

//Other Functions
std::string Dictionary::to_string() const {
    std::string out= "";
    inOrderString(out, this->root);
    return out;
}

std::string Dictionary::pre_string() const {
    std::string out = "";
    preOrderString(out, this->root);
    return out;
}

bool Dictionary::equals(const Dictionary &D) const {
    std::string cmp1 = this->to_string();
    std::string cmp2 = D.to_string();
    if (cmp1 == cmp2){
        return true;
    } else{
        return false;
    }
}

//Overloaded
std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
    std::string out = D.to_string();
    stream << out << std::endl;
    return stream;
}

bool operator==( const Dictionary& A, const Dictionary& B ){
    return A.equals(B);
}

Dictionary& Dictionary::operator=(const Dictionary &D) {
    if (this != &D) {
        this->clear();
        if (D.root != D.nil) {
            this->root = new Node(D.root->key, D.root->val);
            this->num_pairs = D.num_pairs;
            preOrderInsert(D.root, D.nil);
        }
    }
    return *this;
}



