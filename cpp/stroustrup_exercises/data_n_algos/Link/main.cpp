#include "Link.h"
#include "SingleLL.h"
#include <iostream>


void test_link() {
    Link *norse_gods = new Link {"Thor"};
    norse_gods = norse_gods->insert(new Link{"Odin"});
    norse_gods = norse_gods->insert(new Link{"Zeus"});
    norse_gods = norse_gods->insert(new Link{"Freia"});

    Link *greek_gods = new Link {"Hera"};
    greek_gods = greek_gods->insert(new Link{"Athena"});
    greek_gods = greek_gods->insert(new Link{"Mars"});
    greek_gods = greek_gods->insert(new Link{"Poseidon"});

    // fix greek god of war
    Link *p = greek_gods->find("Mars");
    if (p)
        p->set_value("Ares");

    // fix Zeus's place
    p = norse_gods->find("Zeus");
    if (p) {
        if (p == norse_gods)
            norse_gods = p->next();
        p->erase();
        greek_gods = greek_gods->insert(p);
    }

    print_all(norse_gods);
    print_all(greek_gods);
}

void test_sinlgell() {
    SingleLL *norse_gods {
        new SingleLL {God {"Odin", "Norse", "Sleipnir", "Gungir"}}};
    norse_gods = norse_gods->add_ordered(
            new SingleLL {God {"Thor", "Norse", "", "Hammer"}});
    norse_gods = norse_gods->add_ordered(
            new SingleLL {God {"Freia", "Norse", "", ""}});
    print_all(norse_gods);
}

int main() {

    //test_link();
    test_sinlgell();

    return 0;
}

