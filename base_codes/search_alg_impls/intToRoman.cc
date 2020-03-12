#include <cstdio>
#include <vector>
#include <string>
#include <map>

#include "../search_algs.h"

std::string search::intToRoman(int num) { // 1994
    std::string result = "";
    std::pair<int ,char> int2roman[7] = {{1, 'I'},
                                        {5, 'V'},
                                        {10, 'X'},
                                        {50, 'L'},
                                        {100, 'C'},
                                        {500, 'D'},
                                        {1000, 'M'}};

    for (int i=6; i>=0;i--) {
        std::string curr = "";
        int curr_num = 0;
        while(num >= int2roman[i].first) {
            num -= int2roman[i].first;
            curr += int2roman[i].second;
            curr_num++;
        }
        if (curr_num == 4) {
            curr = "";
            curr += int2roman[i].second;
            if ((result.back() == 'V' && int2roman[i].second=='I') 
                || (result.back() == 'L'  && int2roman[i].second=='X') 
                || (result.back() == 'D'  && int2roman[i].second=='C')) {
                curr += int2roman[i+2].second;
                result = result.substr(0, result.length() - 1);
            }
            else {
                curr += int2roman[i+1].second;
            }
        }
        result += curr;
    }
    return result;
}


std::string search::intToRoman_v2(int num) { // 1994
    std::string result = "";

    std::map<int, char> int2roman = {{1, 'I'},
                                    {5, 'V'},
                                    {10, 'X'},
                                    {50, 'L'},
                                    {100, 'C'},
                                    {500, 'D'},
                                    {1000, 'M'}};
    int arr[4][2] = {{1, 5}, {10, 50}, {100, 500}, {1000, 0}};
    for (int i=3; i>=0; i--) {
        if (num < arr[i][0]) continue;
        std::string curr = "";
        int num_curr = num / arr[i][0];
        num = num % arr[i][0];
        
        if (num_curr == 9) {
            curr += int2roman[arr[i][0]];
            curr += int2roman[arr[i+1][0]];
        }
        else if (num_curr >= 5) {
            curr += int2roman[arr[i][1]];
            num_curr -= 5;
            while(num_curr > 0) {
                curr += int2roman[arr[i][0]];
                num_curr--;
            }
        }
        else if (num_curr == 4) {
            curr += int2roman[arr[i][0]];
            curr += int2roman[arr[i][1]];
        }
        else {
            while(num_curr > 0) {
                curr += int2roman[arr[i][0]];
                num_curr--;
            }
        }
        result += curr;
    }
    return result;
}


std::string search::intToRoman_v3(int num) { // 1994
    std::string result = "";

    std::map<int, std::string, std::greater<int>> int2roman = {{1, "I"},
                                    {4, "IV"},
                                    {5, "V"},
                                    {9, "IX"},
                                    {10, "X"},
                                    {40, "XL"},
                                    {50, "L"},
                                    {90, "XC"},
                                    {100, "C"},
                                    {400, "CD"},
                                    {500, "D"},
                                    {900, "CM"},
                                    {1000, "M"}};
    for(std::pair<int, std::string> p : int2roman) {
        while(num>=p.first) {
            result += p.second;
            num -= p.first;
        }
    }
    
    return result;
}