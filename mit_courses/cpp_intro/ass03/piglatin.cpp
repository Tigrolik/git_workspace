#include <iostream>
#include <string>

using namespace std;

const string VOWELS = "aeouy";

const string pigLatinify(const string s)
{
    if (s.size() == 0)
        return s;

    if (s.find("qu") == 0)
        return s.substr(2) + '-' + "quay";
    else if (VOWELS.find(s[0]) != string::npos)
        return s + "way";
    else
        return s.substr(1) + "-" + s[0] + "ay";
}

int main(void)
{
    cout << pigLatinify("quay") << endl;
    cout << pigLatinify("") << endl;
    cout << pigLatinify("apple") << endl;
    cout << pigLatinify("rapture") << endl;

    return 0;
}
