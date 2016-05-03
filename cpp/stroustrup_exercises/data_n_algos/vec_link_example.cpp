#include "Vector.h"
#include "Link.h"
#include <iostream>

void test_vector() {
    Vector v(5);
    for (int i {0}; i < v.size(); ++i) {
        v.set(i, 1.1 * i);
        std::cout << "v{" << i << "]==" << v.get(i) << '\n';
    }
}

void test_link() {
    //Link *norse_gods = new Link {"Thor", nullptr, nullptr};
    //norse_gods = new Link{"Odin", nullptr, norse_gods};
    //norse_gods->next->prev = norse_gods;
    //norse_gods = new Link{"Freia", nullptr, norse_gods};
    //norse_gods->next->prev = norse_gods;
    Link *norse_gods = new Link {"Thor"};
    norse_gods = insert(norse_gods, new Link{"Odin"});
    norse_gods = insert(norse_gods, new Link{"Zeus"});
    norse_gods = insert(norse_gods, new Link{"Freia"});

    Link *greek_gods = new Link {"Hera"};
    greek_gods = insert(greek_gods, new Link{"Athena"});
    greek_gods = insert(greek_gods, new Link{"Mars"});
    greek_gods = insert(greek_gods, new Link{"Poseidon"});

    // fix greek god of war
    Link *p = find(greek_gods, "Mars");
    if (p)
        p->value = "Ares";

    // fix Zeus's place
    p = find(norse_gods, "Zeus");
    if (p) {
        if (p == norse_gods)
            norse_gods = p->next;
        erase(p);
        greek_gods = insert(greek_gods, p);
    }

    print_all(norse_gods);
    print_all(greek_gods);
}

int main() {

    //test_vector();
    test_link();

    return 0;
}

