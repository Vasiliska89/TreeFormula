// TreeFormula.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream> 
#include <iomanip>


int i = 0;
std::string s;
struct tree {
    char id;
    tree* left;
    tree* right;
};
tree* Term();
tree* Atom();
tree* gennode(char s) {
    tree* tmp = new tree;
    tmp->id = s;
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
}
tree* Form() {
    tree* t1 = Term();
    while (s[i] == '+') {
        tree* p = gennode(s[i]);
        p->left = t1;
        i++;
        t1 = Term();
        p->right = t1;
        t1 = p;
    }
    return t1;
}
tree* Term() {
    tree* t1 = Atom();
    while (s[i] == '*') {
        tree* p = gennode(s[i]);
        p->left = t1;
        i++;
        t1 = Atom();
        p->right = t1;
        t1 = p;
    }
    return t1;
}
tree* Atom() {
    tree* t1 = NULL;
    if (isdigit(s[i])) {
        i++;
        return gennode(s[i - 1]);
    }
    else if (s[i] == '!') {
        tree* p = gennode(s[i]);

        i++;
        t1 = Atom();
        p->left = t1;
        t1 = p;
    }
    else if (s[i] == '(') {
        i++;
        t1 = Form();
        i++;
    }
    return t1;
}
void show(tree* t, int n) {
    if (t != NULL) {
        show(t->left, n + 1);
        std::cout << std::setw(n * 3) << t->id << std::endl;
        show(t->right, n + 1);
    }
}
int postorder(tree* t) {
    if (t->id == '!') {
        return(!postorder(t->left));
    }
    else {
        if (isdigit(t->id)) return t->id=='1'? 1:0;
        else {
            if (t->id == '+')return postorder(t->left) || postorder(t->right);
            else if (t->id == '*')return postorder(t->left) && postorder(t->right);
        }
    }
}
int main()
{
    std::ifstream file("input.txt");
    std::getline(file, s);
    tree* t1 = Form();
    show(t1, 1);
    std::cout << "\nAnswer: " << postorder(t1);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
