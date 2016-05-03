#include <iostream>
#include <cstring>

void word_seq() {
    using namespace std;

    constexpr int maxlen = 1024, maxwords = 50;

    char s_in[maxlen] = ""; // var to read into
    char str_arr[maxwords][maxlen]; // list of words
    int i = 0; // track the number of words (array's length)

    cout << "Enter a word (type \"Quit\" to quit): ";
    // using 'cin' since we take words, not expressions (ignore spaces)
    cin >> s_in;
    while (strcmp(s_in, "Quit")) {
        bool b = true; // word is not in the array
        // go through the list of words
        for (int j = 0; j < i; ++j) {
            // compare given word with the current in the list
            int cmp_val = strcmp(s_in, str_arr[j]);
            if (cmp_val <= 0) {
                // if the word is "smaller", then insert it, otherwise the
                // words are equal and we ignore the word
                if (cmp_val != 0) {
                    // move the strings (note increasing 'i')
                    for (int k = i++; k > j; --k) {
                        strcpy(str_arr[k], str_arr[k - 1]);
                    }
                    // insert the word
                    strcpy(str_arr[j], s_in);
                }
                // flag that the word has already been inserted into the list
                b = false;
                break;
            }
        }

        // if the word is "bigger" than all the others, push back
        if (b)
            strcpy(str_arr[i++], s_in);

        cout << "You have entered: " << s_in << endl;
        cout << "Enter a word (type \"Quit\" to finish): ";
        cin >> s_in;
    }
    // add an end of line sign as a sentinel node
    strcpy(str_arr[i], "\0");

    // display the list of words
    for (int j = 0; j < i; ++j)
        cout << str_arr[j] << ' ';
    // number of world (list's size)
    cout << "\b\nArray's size = " << i << endl;
}

int find_pair_in_str(const char *str, const char pair_ch[2]) {
    if (str[0] == '\0' || str[1] == '\0')
        return 0;
    int len {0};
    for (int i = 1; str[i] != '\0'; ++i) {
        if ((str[i - 1] == pair_ch[0]) && (str[i] == pair_ch[1]))
            ++len;
    }
    return len;
}

int find_pair_in_str2(const std::string str, const std::string pair_str) {
    if (str[0] == '\0' || str[1] == '\0')
        return 0;
    int len {0};
    for (int i = 1; str[i] != '\0'; ++i) {
        if ((str[i - 1] == pair_str[0]) && (str[i] == pair_str[1]))
            ++len;
    }
    return len;
}

int main() {

    using namespace std;
    // word_seq();
    // int s = find_pair_in_str("helllllo", "ll");
    int s = find_pair_in_str("xabaacbaxabb", "ab");
    cout << s << endl;
    cout << find_pair_in_str2("xabaabbbaabababasdf", {'a', 'b'}) << endl;

    return 0;
}
