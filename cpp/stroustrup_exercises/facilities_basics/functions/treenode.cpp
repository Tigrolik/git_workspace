#include <iostream>
#include <vector>

using namespace std;

struct Tnode {
    string word;
    int count;
    Tnode *left;
    Tnode *right;
};

//Tnode create_node(const int c, const string &s) {
//    struct Tnode node;
//    node.word = s;
//    node.left = nullptr;
//    node.right = nullptr;
//    node.count = c;
//    return node;
//}

void create_node(Tnode *root, const int c, const string &s) {
    if (root == nullptr) {
        root->word = s;
        root->count = 1;
        root->left = nullptr;
        root->right = nullptr;
        return;
    }
}

void add_node(struct Tnode *root, const string &s) {
    Tnode *node = root;
    int c {node->count};
    while (node != nullptr) {
        if (s < node->word) {
            if (node->left == nullptr) {
                //struct Tnode temp = create_node(c + 1, s);
                //node->left = &temp;
                //create_node(node->left, c + 1, s);
                node->left->word = s;
                node->left->left = nullptr;
                node->left->right = nullptr;
                node->left->count = c + 1;
                return;
            } else {
                node = node->left;
                c = node->count;
            }
        } else if (s > node->word) {
            if (node->right == nullptr) {
                node->right->word = s;
                node->right->left = nullptr;
                node->right->right = nullptr;
                node->right->count = c + 1;
                return;
            } else {
                node = node->right;
                c = node->count;
            }
        } else {
            cout << "Warning: word is in the tree, no new node created\n";
            return;
        }
    }
    node->word = s;
    node->left = nullptr;
    node->right = nullptr;
    node->count = c + 1;
}

void add_words(struct Tnode *tn) {
    string s;
    //cin >> s;
    //*tn = create_node(1, s);
    //create_node(tn, 1, s);
    vector<string> words {"small", "big", "aero"};
    for (const auto &w: words)
        add_node(tn, w);
    //while (cin) {
    //    cin >> s;
    //    add_node(tn, s);
    //}
}

void display_node(const struct Tnode *node) {
    cout << node->word << ' ' << node->count << endl;
}

int main() {
    struct Tnode root {"", 0, nullptr, nullptr};
    add_words(&root);
    display_node(&root);

    return 0;
}

