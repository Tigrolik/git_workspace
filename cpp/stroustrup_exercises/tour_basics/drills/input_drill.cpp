#include <iostream>

inline void simple_error(std::string s) {
    std::cerr << "error: " << s << '\n';
    exit(1);
}

int main() {

    using namespace std;

    cout << "Please, enter the name of the person you want to write to\n";
    string first_name {};
    cin >> first_name;

    cout << "Dear " << first_name << ",\n";
    cout << "How you doing?\nI am fine by the way, missing you every day\n";

    cout << "Now enter the name of your friend (another person)\n";
    string friend_name {};
    cin >> friend_name;

    cout << "Have you seen " << friend_name << " lately?\n";

    char friend_gender {0};
    cout << "Enter the gender of your friend (m/f): ";
    cin >> friend_gender;

    cout << "If you see " << friend_name << " please ask " <<
        (friend_gender == 'f' ? "her" : "him") << " to call me.\n";

    cout << "Enter the age of the recipient: ";
    int age {};
    cin >> age;

    cout << "I hear you just had a birthday and you are " << age <<
        " years old.\n";

    if (age < 1 || age > 111)
        simple_error("You are kidding!");
    else if (age < 12)
        cout << "Next year you will be " << age + 1 << ".\n";
    else if (age == 17)
        cout << "Next year you will be able to vote.\n";
    else if (age > 70)
        cout << "I hope you are enjoying retirement\n";

    cout << "Yours sincerely,\n\nDavid\n";
}
