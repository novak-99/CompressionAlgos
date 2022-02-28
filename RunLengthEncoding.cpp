#include <iostream>
#include <map>
#include <string>

 std::map<char, int> RLE(std::string &data){ // Data is in form of str.
    std::map<char, int> compressedData; 
    for(int i = 0; i < data.length(); i++){
        if(compressedData.find(data[i]) != compressedData.end()){ // If char already exists.
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

