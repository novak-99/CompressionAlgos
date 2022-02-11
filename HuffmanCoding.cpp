#include <iostream>
#include <vector>
#include <map>
#include <string>

class Node{
    public: 
        Node(int frequency){
            this->frequency = frequency; 
        }
        // Setters
        void setData(char datum){
            this->datum = datum;
        }
        void setLeft(Node* left){
            this->left = left; 
        }
        void setRight(Node* right){
            this->right = right;
        }
        // Getters
        int getFrequency(){
            return frequency;
        }
        char getData(){
            return datum;
        }
        Node* getLeft(){
            return left; 
        }
        Node* getRight(){
            return right;
        }
    private:
        int frequency;
        char datum; 
        Node* left = nullptr; 
        Node* right = nullptr; 
};

double sumAllElements(std::vector<double>& vec){
    double sum = 0; 
    for(int i = 0; i < vec.size(); i++){
        sum += vec[i];
    }
    return sum;
}

int findMaxElement(std::vector<double>& vec){
    return std::max_element(vec.begin(), vec.end()) - vec.begin();
}

// More efficient to use map, but two vectors were used to simplify vector operations. 
Node* createHuffmanTree(std::map<int, char> data, std::vector<double> frequencies){
    double sum = sumAllElements(frequencies);
    Node* root = new Node(sum);

    std::vector<Node*> rightTree; 
    std::vector<Node*> leftTree;

    leftTree.push_back(root);

    for(int i = 0; !frequencies.empty(); i++){

        int maxIndex = findMaxElement(frequencies);
        sum -= frequencies[maxIndex];

        rightTree.push_back(new Node(frequencies[maxIndex]));
        rightTree[rightTree.size() - 1]->setData(data[frequencies[maxIndex]]);

        leftTree.push_back(new Node(frequencies[maxIndex]));
        leftTree[leftTree.size() - 2]->setLeft(leftTree[leftTree.size() - 1]);
        leftTree[leftTree.size() - 2]->setRight(rightTree[rightTree.size() - 1]);

        frequencies.erase(frequencies.begin() + maxIndex);

        if(frequencies.size() == 1){ 
            int maxIndex = findMaxElement(frequencies);
            leftTree[leftTree.size() - 1]->setData(data[frequencies[maxIndex]]);
            std::cout << leftTree.size() << std::endl;
            std::cout << rightTree.size() << std::endl;
            break;
        }
    }
    return root;
}

int main(){
    std::map<int, char> data; 
    data.insert(std::pair<int,char>(1, 'a'));
    data.insert(std::pair<int,char>(78, 'b'));
    data.insert(std::pair<int,char>(5, 'c'));
    Node* root = createHuffmanTree(data, {1, 78, 5});
    std::cout << root->getRight()->getData() << std::endl;
}