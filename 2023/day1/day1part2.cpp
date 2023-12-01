#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main() {

    std::vector<std::string> lines;
    std::string spelled_digits[9] = {
        "one",
        "two",
        "three",
        "four",
        "five",
        "six",
        "seven",
        "eight",
        "nine"
    };

    std::ifstream in;
    std::string tmp;
    in.open("input");

    while(in >> tmp)
        lines.push_back(tmp);

    for(auto& line : lines){
        for(auto& ch : line)
            ch = tolower(ch);
        
        auto pos = std::string::npos;
        int index = -1;
        for(int i = 0; i < 9; i++)
            if(line.find(spelled_digits[i]) != std::string::npos)
                if(pos == std::string::npos || line.find(spelled_digits[i]) < pos){
                    pos = line.find(spelled_digits[i]);
                    index = i;
                }
        
        if(index != -1)
            line.insert(pos, std::to_string(index+1));

        pos = std::string::npos;
        index = -1;
        for(int i = 0; i < 9; i++)
            if(line.rfind(spelled_digits[i]) != std::string::npos){
                if(pos == std::string::npos || line.rfind(spelled_digits[i]) > pos){
                    pos = line.rfind(spelled_digits[i]);
                    index = i;
                }
        }
        if(index != -1)
            line.insert(pos, std::to_string(index+1));

    }

    std::vector<int> out;
    int sum = 0;

    for(auto& line : lines){
        std::string num = "  ";

        for(int i = 0; i < line.size(); i++)
            if(isdigit(line[i])){
                num[0] = line[i];
                break;
            }
        for(int i = line.size() - 1; i >= 0; i--)
            if(isdigit(line[i])){
                num[1] = line[i];
                break;
            }

        out.push_back(stoi(num));
        sum += out.back();
    }

    printf("sum: %d\n", sum);

    return 0;

}
