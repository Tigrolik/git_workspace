#include <iostream>
#include <iterator>

using namespace std;

void loop_test() {
    const int max_length {5};
    const char input_line[max_length] {'a', 'p', '?', '!', '?'};
    int quest_count {0};

    for (auto i = 0; i < max_length; ++i)
        if (input_line[i] == '?')
            ++quest_count;

    cout << quest_count << endl;

    auto i = 0;
    while (i < max_length)
        if (input_line[i++] == '?')
            ++quest_count;
    cout << quest_count << endl;

    const char *p = &input_line[0];
    while (*p != '\0')
        if ('?' == *p++)
            ++quest_count;
    cout << quest_count << endl;

    for (auto q = begin(input_line); q != end(input_line); ++q)
        if ('?' == *q)
            ++quest_count;
    cout << quest_count << endl;

    for (p = &input_line[0]; *p != '\0'; ++p)
        if (*p == '?')
            ++quest_count;
    cout << quest_count << endl;
}

#if 0
void err_react(int a, int b) {
    if (a = 3)
        cout << "eh?\n";
    if (a & 077 == 0)
        cout << "oct..\n";
    //a := b + 1;
}
#endif

int my_atoi(const char *s) {
    if (s[0] == '\0')
         return 0;
     // use zero's ('0') code to 'detect' digit symbols
    const char num_zero {'0'};
    // res - accumulate the result
    int res {0};
    // set flag if all symbols are digits
    bool b {true};
    // multiplication quotient and starting symbol index (for digital)
    int q {10}, f {0};

    if (s[0] == '0') { // octal
        if (s[1] == 'x') { // hexadecimal
            q = 16;
            f = 2;
        } else {
            q = 8;
            f = 1;
        }
    }

    // go through the character array
    for (auto i = f; s[i] != '\0'; ++i) {
        char c;
        switch (toupper(s[i])) {
            case 'A':
                c = 10;
                break;
            case 'B':
                c = 11;
                break;
            case 'C':
                c = 12;
                break;
            case 'D':
                c = 13;
                break;
            case 'E':
                c = 14;
                break;
            case 'F':
                c = 15;
                break;
            default:
                c = s[i] - num_zero;
                break;
        }
        // check if the symbol is a digit
        if ((c >= 0) && (c < q)) {
            res = res * q + c;
        } else {
            // character const notations
            if (((toupper(s[i]) == 'U') || (toupper(s[i]) == 'L')) &&
                    ((s[i + 1] == '\0') || ((s[i + 1] != '\0') &&
                        (toupper(s[i + 1]) == 'L') && s[i + 2] == '\0')))
                break;
            // if the symbol is not a digit then quit the loop
            b = false;
            break;
        }
    }
    if (b)
        return res;
    // if one of the symbols is not a digit then return 0
    else
        return 0;
}

char *my_itoa(int i, char b[]) {
    const char num_zero {'0'};

    while (i > 0) {
        cout << i % 10 << endl;
        i /= 10;
        *b = i + num_zero;
        ++b;
    }

    return b;
}

int main()
{
    // loop_test();
    // cout << my_atoi("2980740") << endl;
    // cout << my_atoi("0437") << endl;
    // cout << my_atoi("0x13ful") << endl;
    // cout << 0437ULL << endl;
    // cout << 0x13fu << endl;
    int i {2734};
    while (i > 0) {
        cout << i % 10 << endl;
        i /= 10;
    }

    char b[] = "";
    char *p =  my_itoa(i, b);
    for (; *p != '\0'; ++p)
        cout << *p << endl;

    return 0;
}
