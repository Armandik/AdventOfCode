#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct number{

    int value;
    int leftmostCol;
    int rightmostCol;
    int row;
};

std::vector<number> parseNumbers(std::vector<std::string> lines){

    std::vector<number> numbers;
    for(int row = 0; row < lines.size(); row++){
        
        std::string num = "";
        for(int col = 0; col < lines[row].size(); col++){

            if(isdigit(lines[row][col]))
                num.push_back(lines[row][col]);
            else
                if(num.size() != 0){
                    number tmp = {
                        stoi(num),
                        col - num.size(),
                        col - 1,
                        row
                    };
                    numbers.push_back(tmp);
                    num.clear();
                }
        }
        if(num.size() != 0){
            number tmp = {
                stoi(num),
                lines[row].size() - num.size(),
                lines[row].size() - 1,
                row
            };
            numbers.push_back(tmp);
            num.clear();
        }
    }

    return numbers;
}

bool validNumber(number num, const std::vector<std::string> lines){

    // check top row
    for(int col = num.leftmostCol -1; col <= num.rightmostCol + 1; col++)
        if(!isdigit(lines[num.row-1][col]) && lines[num.row-1][col] != '.')
            return true;

    // check bottom row
    for(int col = num.leftmostCol -1; col <= num.rightmostCol + 1; col++)
        if(!isdigit(lines[num.row+1][col]) && lines[num.row+1][col] != '.')
            return true;

    // check left column
    if(!isdigit(lines[num.row][num.leftmostCol - 1]) && lines[num.row][num.leftmostCol - 1] != '.')
        return true;

    // check right column
    if(!isdigit(lines[num.row][num.rightmostCol + 1]) && lines[num.row][num.rightmostCol + 1] != '.')
        return true;

    return false;
}

int main(){

    std::vector<std::string> lines;
    std::ifstream in;
    std::string tmp;
    int sum = 0;

    in.open("input");
    while(std::getline( in, tmp)){
        tmp.insert(tmp.begin(), '.');   // left padding
        tmp.push_back('.');             // right padding
        lines.push_back(tmp);
    }
    
    tmp = std::string(lines[0].size(), '.');
    lines.insert(lines.begin(), tmp);   // top padding
    lines.push_back(tmp);               // bottom padding

    std::vector<number> numbers;
    numbers = parseNumbers(lines);

    // Part One
    for(auto& num: numbers)
        if(validNumber(num, lines))
            sum += num.value;

    printf("Sum for Part One: %d\n", sum);

    // Part Two
    sum = 0;

    for(int row = 0; row < lines.size(); row++)
        for(int col = 0; col < lines[row].size(); col++){

            if(lines[row][col] != '*')
                continue;
                    
            std::vector<number> adjNums;
            bool numfound = false;
            for(int i = col - 1; i <= col + 1; i++)
                if(isdigit(lines[row - 1][i]) || isdigit(lines[row + 1][i])) // check top and bottom row
                    numfound = true;
            
            if(isdigit(lines[row][col - 1]) || isdigit(lines[row][col + 1])) // check left and right col
                numfound = true;
            
            if(numfound){
                for(auto& num : numbers){
                    if( (row == num.row && num.rightmostCol == col - 1) ||    // number on the left
                        (row == num.row && num.leftmostCol  == col + 1))      // number on the right
                            adjNums.push_back(num);
                    
                    if(row - 1 == num.row || row + 1 == num.row)
                        for(int i = col - 1; i <= col + 1; i++)
                            if(i == num.rightmostCol || i == num.leftmostCol){
                                adjNums.push_back(num);
                                break;
                            }
                }

                if(adjNums.size() > 2)
                    exit(EXIT_FAILURE);
                
                if(adjNums.size() == 2)
                    sum += adjNums[0].value*adjNums[1].value;
                
                adjNums.clear();
            }
            
        }

        printf("Sum for Part Two: %d\n", sum);

    return 0;
}