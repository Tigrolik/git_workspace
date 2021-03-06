#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Tnode {
    string word;
    int count;
    Tnode *left;
    Tnode *right;
};

void insert(Tnode *&p, const std::string &s) {
    if (!p)
        p = new Tnode {s, 1, nullptr, nullptr};
    else if (p->word < s)
        insert(p->right, s);
    else
        insert(p->left, s);
    ++(p->count);
}

void add_words(Tnode *t) {
    string s;
    vector<string> words {"small", "big", "aero"};
    for (const auto &w: words)
        insert(t, w);
}

std::ostream& operator<<(std::ostream &os, const Tnode *t) {
    if (t) os << t->word << ", " << t->left << t->right;
    return os;
}

void print_all(Tnode *t) {
    std::cout << t << t->count << '\n';
}

void print_preorder(Tnode *t) {
    std::cout << t->word << ", ";
    if (t->left)
        print_preorder(t->left);
    if (t->right)
        print_preorder(t->right);
}

void print_postorder(Tnode *t) {
    if (t->left)
        print_preorder(t->left);
    if (t->right)
        print_preorder(t->right);
    std::cout << t->word << ", ";
}

void print_inorder(Tnode *t) {
    if (t->left)
        print_preorder(t->left);
    std::cout << t->word << ", ";
    if (t->right)
        print_preorder(t->right);
}

void print_levelorder(Tnode *t) {
    std::queue<const Tnode*> q;
    q.push(t);
    while (!q.empty()) {
        const Tnode *n = q.front();
        q.pop();
        std::cout << n->word << ", ";
        if (n->left) q.push(n->left);
        if (n->right) q.push(n->right);
    }
}

int main() {
    Tnode *root = new Tnode {"banana", 1, nullptr, nullptr};
    insert(root, "apple");
    insert(root, "orange");
    insert(root, "algo");
    add_words(root);

    //print_all(root);
    std::cout << "preorder printing\n";
    print_preorder(root);
    std::cout << root->count << '\n';

    std::cout << "postorder printing\n";
    print_postorder(root);
    std::cout << root->count << '\n';

    std::cout << "inorder printing\n";
    print_inorder(root);
    std::cout << root->count << '\n';

    std::cout << "levelorder printing\n";
    print_levelorder(root);
    std::cout << root->count << '\n';


    return 0;
}

