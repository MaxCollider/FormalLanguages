#include <string>
#include <cassert>
using namespace std;

int solve(string rpn, string word);

void checker(string rpn, string word, int answer_right = -1) {
    int answer = solve(rpn, word);
    if (answer != answer_right) {
        cout << "Wrong answer: " << answer << "Expected: " << answer_right;
        throw logic_error("wrong answer");
    }
    cout << "Correct answer" << endl;

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
    checker("ab+*", "bacba", 2)

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
