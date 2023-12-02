#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

void parseLine(std::string line, std::vector<std::vector<std::vector<int>>> &games){

    std::vector<std::string> plays;

    auto pos = line.find(':');
    line.replace(pos, 1, "\n");
    pos = line.find(';');
    while(pos != std::string::npos){
        line.replace(pos, 1, "\n");
        pos = line.find(';');
    }

    std::stringstream s(line);
    std::string temp_str = "";
    while(std::getline(s, temp_str))
        plays.push_back(temp_str);
    plays.erase(plays.begin());

    std::vector<std::vector<int>> game;

    for(auto& play : plays){

        std::vector<std::string> nums;
        std::string tmp_num;
        for(int i = 0; i < play.size(); i++)
            if(play[i] != ','){
                tmp_num.push_back(play[i]);
            } else {
                nums.push_back(tmp_num);
                tmp_num.clear();
            }
        nums.push_back(tmp_num);
        tmp_num.clear();

        std::vector<int> temp_play(3);
        temp_play[0] = 0;
        temp_play[1] = 0;
        temp_play[2] = 0;
        for(auto& num : nums){
            tmp_num.clear();
            for(int i = 0; i < num.size(); i++)
                if(isdigit(num[i]))
                    tmp_num.push_back(num[i]);

            if(num.find("red") != std::string::npos)
                temp_play[0] = std::stoi(tmp_num);
            if(num.find("green") != std::string::npos)
                temp_play[1] = std::stoi(tmp_num);
            if(num.find("blue") != std::string::npos)
                temp_play[2] = std::stoi(tmp_num);
            
        }
        game.push_back(temp_play);
    }

    games.push_back(game);
}

int main(){

    std::vector<std::string> lines;

    std::ifstream in;
    std::string tmp;
    int sum = 0;
    in.open("input");

    while(std::getline( in, tmp))
        lines.push_back(tmp);
        
    std::vector<std::vector<std::vector<int>>> games;

    for(auto& line : lines)
        parseLine(line, games);
/* 
    for(auto& game: games)
        for(auto& play : game)
            std::cout << "red "   << play[0]
                    << " green "  << play[1]
                    << " blue "   << play[2] << "\n";
 */
    for(int game_id = 0; game_id < games.size(); game_id++){   
        int max_num[3] = {0, 0, 0};
        for(int play_id = 0; play_id < games[game_id].size(); play_id++){
            if(games[game_id][play_id][0] > max_num[0])
                max_num[0] = games[game_id][play_id][0];

            if(games[game_id][play_id][1] > max_num[1])
                max_num[1] = games[game_id][play_id][1];

            if(games[game_id][play_id][2] > max_num[2])
                max_num[2] = games[game_id][play_id][2];
        }
        sum += max_num[0]*max_num[1]*max_num[2];
    }
    std::cout << sum;
    return 0;
}