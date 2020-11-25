#include <string>
#include <cassert>
using namespace std;

int solve(string rpn, string word);

void checker(string rpn, string word, int answer_right = -1) {
    int answer = solve(rpn, word);
    if (answer != answer_right) {
//        cout << -1;
        cout << "Wrong answer: " << answer << "Expected: " << answer_right;
        throw logic_error("wrong answer");
    }
    cout << "Correct answer" << endl;

}

void test() {
    checker("ab+c.aba.*.bac.+.+*", "abacb", 4);
    checker("acb..bab.c.*.ab.ba.+.+*a.", "cb", 0);
    checker("1", "ackba", 0);
    checker("11+", "ackba", 0);
    checker("11.", "ackba", 0);
    checker("1a.", "ackba", 1);
    checker("1a+", "ackba", 1);
    checker("a1.", "ackba", 1);
    checker("a1+", "ackba", 1);
    checker("ac1..", "ackba", 2);
    checker("aca..", "ackba", 0);
    checker("ac1..", "ackba", 2);

    // a(b+1)c
    checker("ab1+.c.", "", 0);
    checker("ab1+.c.", "a", 0);
    checker("ab1+.c.", "b", 0);
    checker("ab1+.c.", "c", 0);
    checker("ab1+.c.", "ac", 2);
    checker("ab1+.c.", "acqwerfsd", 2);
    checker("ab1+.c.", "abcasj", 3);
}
