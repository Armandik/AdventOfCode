#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <math.h>

void parseInput(std::vector<std::string> &lines, 
                std::vector<std::vector<int>> &winNums,
                std::vector<std::vector<int>> &myNums){

    for(auto& line: lines){
        
        winNums.push_back(std::vector<int>());
        myNums.push_back(std::vector<int>());
        std::string tmp;
        int pos_colon, pos_bar = 0;

        for(int i = 0; i < line.size(); i++){
            if(line[i] == ':')
                pos_colon = i;
            if(line[i] == '|')
                pos_bar = i;
        }

        for(int i = pos_colon; i < pos_bar; i++){
            
            if(isdigit(line[i]))
                tmp.push_back(line[i]);
            
            if(line[i] == ' ' && tmp.size() != 0){
                winNums.back().push_back(stoi(tmp));
                tmp.clear();
            }
        }

        for(int i = pos_bar; i < line.size(); i++){

            if(isdigit(line[i]))
                tmp.push_back(line[i]);
            
            if(line[i] == ' ' && tmp.size() != 0){
                myNums.back().push_back(stoi(tmp));
                tmp.clear();
            }
        }

        if(tmp.size() != 0)
            myNums.back().push_back(stoi(tmp));
    }

}

int main(){

    std::vector<std::string> lines;
    std::ifstream in;
    std::string tmp;
    int sum = 0;

    in.open("input");
    while(std::getline( in, tmp))
        lines.push_back(tmp);
    
    std::vector<std::vector<int>> winNums;
    std::vector<std::vector<int>> myNums;

    parseInput(lines, winNums, myNums);
    std::vector<int> quantity(winNums.size(), 1);

    // Part One
    for(int i = 0; i < winNums.size(); i++){
        int winningNums = 0;
        for(auto& myNum : myNums[i])
            if(std::find(winNums[i].begin(), winNums[i].end(), myNum) != winNums[i].end())
                winningNums++;
        
        // Part One
        sum += pow(2, winningNums - 1);

        // Part Two
        for(int j = 1; j <= winningNums; j++)
            if((i+j) < quantity.size())
                quantity[i+j] += quantity[i];

    }

    printf("Sum for Part One: %d\n", sum);

    for(auto& q : quantity)
        sum += q;

    printf("Sum for Part Two: %d\n", sum);

    return 0;
}