#include <iostream>
#include <map>
#include <string>

 std::map<char, int> RLE(std::string &data){ // Data is in form of str.
    std::map<char, int> compressedData; 
    for(int i = 0; i < data.length(); i++){
        if(i > 0 && data[i] == data[i - 1]){
            compressedData[data[i]]++;
            continue; 
        }
        compressedData.insert(std::pair<char,int>(data[i], 1));
    }
    return compressedData;
}

void printData(std::map<char, int>& compressedData){
    for(auto [m, v] : compressedData){
        std::cout << m << v;
    }
    std::cout << std::endl;
}

int main(){
    std::string data("aaaabbbbccccddd");
    auto compressedData = RLE(data);
    printData(compressedData);
    return 0; 
}

