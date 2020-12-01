#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
#include <stack>
#include "tests.h"


int get_child(std::stack<int>& stack) {
    if (stack.empty())
        throw std::out_of_range("stack is empty - get_child is impossible!");
    int child = stack.top();
    stack.pop();
    return child;
}

int solve(std::string reg, std::string str) {
    if (reg.empty())
        throw std::logic_error("Empty RegularExpression");

    std::vector<std::vector<std::vector<bool>>> dp(
            reg.length() + 1,
    std::vector<std::vector<bool>>(str.size() + 1,
            std::vector<bool>(str.size() + 1, false)));

    std::stack<int> stack;

    for (int l = 0; l < reg.size(); ++l) {

        if (reg[l] == '1') {
            for (int i = 0; i < str.size(); ++i) {
                dp[l][i][i] = true;
            }
        }

        if (reg[l] >= 'a' && reg[l] <= 'c') {
            for (int i = 0; i < str.size(); ++i) {
                if (str[i] == reg[l])
                dp[l][i][i + 1] = true;
            }
        }

        if (reg[l] == '.') {

            int child2 = get_child(stack);
            int child1 = get_child(stack);
            for (int i = 0; i < str.size() + 1; ++i) {
                for (int j = i; j < str.size() + 1; ++j) {
                    for (int inter = i; inter <= j; ++inter) {
                        dp[l][i][j] = dp[l][i][j] || (dp[child1][i][inter] && dp[child2][inter][j]);
                    }
                }
            }

        }

        if (reg[l] == '+'){
            int child2 = get_child(stack);
            int child1 = get_child(stack);
            for (int i = 0; i < str.size() + 1; ++i) {
                for (int j = i; j < str.size() + 1; ++j) {
                    dp[l][i][j] = dp[child1][i][j] || dp[child2][i][j];
                }
            }
        }

        if (reg[l] == '*'){
            int child = get_child(stack);
            for (int i = 0; i < str.size() + 1; ++i) {
                dp[l][i][i] = true;
            }
            for (int i = 0; i < str.size() + 1; ++i) {
                for (int j = i; j < str.size() + 1; ++j) {
                    for (int inter = i; inter <= j; ++inter) {
                        dp[l][i][j] = dp[l][i][j] || (dp[l][i][inter] && dp[child][inter][j]);
                    }
                }
            }
        }
        stack.push(l);
    }

    if (stack.size() > 1)
        throw std::invalid_argument("RegExpr in not a valid: too many operands");
    int longest_pref = 0;

    for (int len_of_pref = 0; len_of_pref < str.size() + 1; ++len_of_pref) {
        if (dp[reg.size() - 1][0][len_of_pref]) {
            longest_pref = len_of_pref;
        }
    }

//    cout << longest_pref;
    return longest_pref;
}

int main(){
    std::string reg, str;
    std::cin >> reg >> str;
    std::cout << solve(reg, str);
//    test();

}