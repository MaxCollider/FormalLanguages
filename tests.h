#include <string>
#include <cassert>


int wrap_solve(std::string reg, std::string str);

void checker(std::string reg, std::string str, int answer_right = -1) {
    int answer = wrap_solve(reg, str);
    if (answer != answer_right) {
        std::cout << "Wrong answer: " << answer << "Expected: " << answer_right;
        throw std::logic_error("wrong answer");
    }
    std::cout << "Correct answer" << std::endl;

}

void test() {
    checker("ab+c.aba.*.bac.+.+*", "abacb", 4);
    checker("acb..bab.c.*.ab.ba.+.+*a.", "cb", 0);
    checker("1", "abc", 0);
    checker("1a.", "abc", 1);
    checker("1a+", "abc", 1);
    checker("a1.", "abc", 1);

    checker("ab.", "ba", 0);
    checker("ab.", "ab", 2);
    checker("ab+", "baba", 1);
    checker("ab+*", "bacba", 2);

    checker("a*ab+c..", "abc", 3);
    checker("a*ab+c..", "acb", 2);
    checker("ac.b+*c.*", "bca", 2);
    checker("ac.b+*c.*", "baca", 0);
    checker("b1+c+ba.*a+b.b+.*", "baka", 1);
    checker("b1+c+ba.*a+b.b+.*", "kaban", 0);

    checker("1a+b+c+*", "abc", 3);

    checker("1a+b+c+*", "baca", 4);
    checker("1a+b+c+*", "baka", 2);
}
