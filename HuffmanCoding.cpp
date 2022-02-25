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

int findMinElement(std::vector<double>& vec){
    return std::min_element(vec.begin(), vec.end()) - vec.begin();
}

void preOrderSearch(Node* root, std::map<char, std::string>& huffmanEncodings, std::string& encodingStr){ // Our encodings are strings. (can convert.)
    // NOTE:
    // LEFT => 1
    // RIGHT => 0

    // If our current node is null at left, it's empty and we don't search it. 
    if (root->getLeft() == nullptr) { 
        huffmanEncodings.insert(std::pair<char,std::string>(root->getData(), encodingStr)); // switch with coding
        return; 
    } 

    encodingStr += "1";
    preOrderSearch(root->getLeft(), huffmanEncodings, encodingStr);
    encodingStr.pop_back();

    // If our current node is null at right, it's empty and we don't search it. 
    if (root->getRight() == nullptr) { 
        huffmanEncodings.insert(std::pair<char,std::string>(root->getData(), encodingStr));
        return; 
    } 

    encodingStr += "0";
    preOrderSearch(root->getRight(), huffmanEncodings, encodingStr);
    encodingStr.pop_back();
}

// More efficient to use map, but two vectors were used to simplify vector operations. 
Node* createHuffmanTree(std::map<int, char> data, std::vector<double> frequencies){
    std::vector<Node*> currentTree; 

    for(int i = 0; !frequencies.empty(); i++){

        int firstMinIndex = findMinElement(frequencies);
        Node* currentNodeLeft = new Node(frequencies[firstMinIndex]);
        // Check if this node already exists, but only when epoch > 0 to avoid seg fault.
        if(i > 0){
            for(int i = 0; i < currentTree.size(); i++){
                if(currentTree[i]->getFrequency() == frequencies[firstMinIndex]){
                    currentNodeLeft = currentTree[i];
                    break;
                }
            }
        }

        frequencies.erase(frequencies.begin() + firstMinIndex);

        // This conditional finds if frequency-datum pair exists in map. 
        // If not, there is no need to set the data field. 
        if(data.find(currentNodeLeft->getFrequency()) != data.end()){ 
            currentNodeLeft->setData(data[currentNodeLeft->getFrequency()]);
        }

        int secondMinIndex = findMinElement(frequencies);
        Node* currentNodeRight = new Node(frequencies[secondMinIndex]); // fr[i_2] > fr[i_1]. Greater always on right. 
        // Check if this node already exists, but only when epoch > 0 to avoid seg fault.
        if(i > 0){
            for(int i = 0; i < currentTree.size(); i++){
                if(currentTree[i]->getFrequency() == frequencies[secondMinIndex]){
                    currentNodeRight = currentTree[i];
                    break;
                }
            }
        }

        frequencies.erase(frequencies.begin() + secondMinIndex);

        // This conditional finds if frequency-datum pair exists in map. 
        // If not, there is no need to set the data field. 
        if(data.find(currentNodeRight->getFrequency()) != data.end()){ 
            currentNodeRight->setData(data[currentNodeRight->getFrequency()]);
        }

        int summedFreq = currentNodeLeft->getFrequency() + currentNodeRight->getFrequency();
        // Pushing back to empty vector exacts a seg fault. This conditional avoids that. 
        if(!frequencies.empty()) 
            frequencies.push_back(summedFreq);
        Node* currentNode = new Node(summedFreq); 

        currentNode->setLeft(currentNodeLeft);

        currentNode->setRight(currentNodeRight);

        currentTree.push_back(currentNode);
    }
    return currentTree[currentTree.size() - 1]; // The final index must be root. 
}

int main(){
    std::map<int, char> data; 
    data.insert(std::pair<int,char>(5, 'a'));
    data.insert(std::pair<int,char>(6, 'b'));
    data.insert(std::pair<int,char>(7, 'c'));
    data.insert(std::pair<int,char>(8, 'd'));
    Node* root = createHuffmanTree(data, {5, 6, 7, 8});
    std::cout << root->getRight()->getRight()->getData() << std::endl;

    std::map<char, std::string> codings; 
    std::string encodingStr = "";  // Init it.
    preOrderSearch(root, codings, encodingStr);

    for(auto [m, v] : codings){
        std::cout << m << ":" << v << std::endl;
    }
}