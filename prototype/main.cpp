#include <iostream>
#include <string>
using namespace std;

class Prototype {
public:
    virtual Prototype* Clone() = 0;
    virtual void show() = 0;

};

class ConcretePrototype1 : public Prototype {
public:
    ConcretePrototype1(string str) {
        m_str = str;
    }
    Prototype* Clone() {
        ConcretePrototype1* p = new ConcretePrototype1(m_str);
        return p;
    }

    void show() {
        cout << m_str <<endl;
    }
private:
    string m_str;
};

class ConcretePrototype2 : public Prototype {
public:
    ConcretePrototype2(int n) {
        m_n = n;
    }
    Prototype* Clone() {
        ConcretePrototype2* p = new ConcretePrototype2(m_n);
        return p;
    }
    void show() {
        cout << m_n <<endl;
    }
private:
    int m_n;
};

int main() {
    Prototype* p1 = new ConcretePrototype1("hello");
    Prototype* p2 = new ConcretePrototype2(100);
    Prototype* p3 = p1->Clone();
    Prototype* p4 = p2->Clone();
    p3->show();
    p4->show();
    delete p1;
    delete p2;
    delete p3;
    delete p4;
    
    return 0;
}