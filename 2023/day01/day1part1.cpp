#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main() {

    std::vector<std::string> lines;

    std::ifstream in;
    std::string tmp;
    in.open("input");

    while(in >> tmp)
        lines.push_back(tmp);

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

    printf("sum: %d", sum);

    return 0;

}
