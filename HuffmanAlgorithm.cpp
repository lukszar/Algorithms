//
//  main.cpp
//  Huffman Algorithm
//
//  Created by Lukasz Szarkowicz on 07.12.2014.
//  Copyright (c) 2014 Lukasz Szarkowicz. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

class Node {
public:
    int probability;
    string codeName = "";
    
    Node(int _probability) {
        probability = _probability;
    }
    
    Node() {
        probability = 0;
    }
};

class Letter : public Node {
public:
    
    char name;
    
    Letter(char _name) {
        name = _name;
    }
};

class Tree {
public:
    Tree *leftChild;
    Tree *rightChild;
    Node *root;
    
    Tree(Letter *letter) {
        this->root = letter;
        this->leftChild = nullptr;
        this->rightChild = nullptr;
    }
    
    Tree(Tree *_a, Tree *_b) {
        this->leftChild = _a;
        this->rightChild = _b;
        this->root = new Node(_a->root->probability + _b->root->probability);
    }
    
    void fillCodeName();
};

void Tree::fillCodeName() {
    
    string codeNameLeft = root->codeName;
    string codeNameRight = root->codeName;
    
    codeNameLeft.append("0");
    codeNameRight.append("1");
    
    if (leftChild) {
        leftChild->root->codeName = codeNameLeft;
    }
    
    if (rightChild) {
         rightChild->root->codeName = codeNameRight;
    }
   
    if (leftChild && rightChild) {
        leftChild->fillCodeName();
        rightChild->fillCodeName();
    } else {
        Letter * letter = (Letter *)root;
        cout << "\nLetter: " << letter->name << " has code: " << letter->codeName;
    }
};

// Point class methods
class Huffman
{
public:
    string sentence;
    vector<Letter *> letters;
    vector<Tree *> trees;
    
    Huffman(string _sentence){
        sentence = _sentence;
    }
    
    Letter * findLetterInVector(char _name);
    Tree * findTheLeastPopularTreeInVector();
    
    void simulate();
};

Letter * Huffman::findLetterInVector(char _name) {
   
    for (int i=0; i<letters.size(); i++) {
        
        if (letters[i]->name == _name) return letters[i];
    }
    
    Letter *newLetter = new Letter(_name);
    letters.push_back(newLetter);
    return newLetter;
};

// method to find the least popular Tree in Vector - not used in simulating
Tree * Huffman::findTheLeastPopularTreeInVector() {
    
    int z = INT_MAX;
    Tree *tmp = nullptr;
    
    for (int i=0; i<trees.size(); i++) {
        
        if (trees[i]->root->probability < z) {
            
            z = trees[i]->root->probability;
            tmp = trees[i];
        }
    }
    
    return tmp;
};

void Huffman::simulate() {
  
    // count probability
    // loop for each char in sentence
    
    cout << "\n=========== Probability for letters =========";

    for (int i=0; i<sentence.length(); i++) {
        Letter *letter = findLetterInVector(sentence[i]);
        letter->probability++;
    }
    
    for (int i=0; i<letters.size(); i++) {
        cout << "\nLetter: " << letters[i]->name << " = " << letters[i]->probability;
    }
    
    cout << "\n\n========= Press enter to generate trees =====";
    getchar();
    
    //generate trees
    for (int i=0; i<letters.size(); i++) {
        Tree *tree = new Tree(letters[i]);
        trees.push_back(tree);
    }
    
    while (trees.size() > 1) {
        sort(trees.begin(), trees.end(), [](Tree * a, Tree * b) {
            return a->root->probability > b->root->probability;
        });
        
        Tree * a = trees.back();
        trees.pop_back();
        
        Tree *b = trees.back();
        trees.pop_back();
        
        Tree *master = new Tree(a, b);
        trees.push_back(master);
    }
    
    cout << "\n\n========== Codes for letters ================";
    Tree * rootTree = trees.back();
    rootTree->fillCodeName();
};

int main(int argc, const char * argv[]) {

    Huffman huffman("abrakadabra");
    huffman.simulate();
    
    cout << "\n\nSentence for Huffman algorithm: " << huffman.sentence;
    
    getchar();
    return 0;
}
