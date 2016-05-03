#include<iostream>

using namespace std;

int main(){

    char c;

    cin.get(c);

    cin.putback(c);

    cin.get(c);

    cout<<'\n'<<c<<" is the next input character.\n";

    return 0;

}
