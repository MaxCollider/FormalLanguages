#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
#include <stack>
#include "tests.h"

using SubwordMatrix = std::vector<std::vector<bool>>;

class Solver {
    std::string reg;
    std::string str;
    std::stack<int> stack;
    std::vector<SubwordMatrix> dp;

public:
    Solver(std::string reg, std::string word) : reg(reg), str(word) {}

private:

    int get_child() {
        if (stack.empty()) {
            throw std::out_of_range("stack is empty - get_child is impossible!");
        }
        int child = stack.top();
        stack.pop();
        return child;
    }

    void Symvol(int num_of_position) {
        for (int i = 0; i < str.size(); ++i) {
            if (str[i] == reg[num_of_position])
                dp[num_of_position][i][i + 1] = true;
        }
    }

    void DotOperator(int num_of_positon) {

        int child2 = get_child();
        int child1 = get_child();
        for (int i = 0; i < str.size() + 1; ++i) {
            for (int j = i; j < str.size() + 1; ++j) {
                for (int inter = i; inter <= j; ++inter) {
                    dp[num_of_positon][i][j] =
                            dp[num_of_positon][i][j] || (dp[child1][i][inter] && dp[child2][inter][j]);
                }
            }
        }
    }

    void PlusOperator(int num_of_positon) {
        int child2 = get_child();
        int child1 = get_child();
        for (int i = 0; i < str.size() + 1; ++i) {
            for (int j = i; j < str.size() + 1; ++j) {
                dp[num_of_positon][i][j] = dp[child1][i][j] || dp[child2][i][j];
            }
        }
    }

    void StarOparator(int num_of_positon) {
        int child = get_child();
        for (int i = 0; i < str.size() + 1; ++i) {
            dp[num_of_positon][i][i] = true;
        }
        for (int i = 0; i < str.size() + 1; ++i) {
            for (int j = i; j < str.size() + 1; ++j) {
                for (int inter = i; inter <= j; ++inter) {
                    dp[num_of_positon][i][j] =
                            dp[num_of_positon][i][j] || (dp[num_of_positon][i][inter] && dp[child][inter][j]);
                }
            }
        }
    }

public:
    int solve() {
        if (reg.empty()) {
            throw std::logic_error("Empty RegularExpression");
        }

        dp.resize(
                reg.length() + 1,
                SubwordMatrix(str.size() + 1,
                              std::vector<bool>(str.size() + 1, false)));


        for (int l = 0; l < reg.size(); ++l) {

            if (reg[l] == '1') {
                for (int i = 0; i < str.size(); ++i) {
                    dp[l][i][i] = true;
                }
            }

            if (reg[l] >= 'a' && reg[l] <= 'c') {
                Symvol(l);
            }

            if (reg[l] == '.') {
                DotOperator(l);
            }

            if (reg[l] == '+') {
                PlusOperator(l);
            }

            if (reg[l] == '*') {
                StarOparator(l);
            }
            stack.push(l);
        }

        if (stack.size() > 1) {
            throw std::invalid_argument("RegExpr in not a valid: too many operands");
        }
        int longest_pref = 0;

        for (int len_of_pref = 0; len_of_pref < str.size() + 1; ++len_of_pref) {
            if (dp[reg.size() - 1][0][len_of_pref]) {
                longest_pref = len_of_pref;
            }
        }

        return longest_pref;
    }
};

int wrap_solve(std::string reg, std::string str) {
    Solver solver(reg, str);
    return solver.solve();
}


int main() {
//    std::string reg, str;
//    std::cin >> reg >> str;
//    std::cout << solve(reg, str);
    test();

}