#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

/**
    有问题：为什么在第二个ClientCode函数中调用的不是 adaptee ？ 而是默认的target？
    原因：在 Adaptor 类中，Request（）函数没有写成const，导致Request（）成为新的函数，而不是重写基类的方法。 
    愚蠢的错误，太折麽了！  
    在 ClientCode函数中，参数类型若为 unique_ptr<Target> target， 则不能传进 unique_ptr<Adaptor> adaptor
    unique_ptr不能进行隐式的类型    

    问：unique_ptr可以从父类转换到子类吗？
    答：不可以，std::unique_ptr不支持从父类指针到子类指针的隐式转换。这是因为在C++中，智能指针的目的是管理动态分配的内存，并确保在合适的时候释放它。
    如果允许将父类指针转换为子类指针，则可能导致在释放时出现未定义的行为，因为父类指针可能指向的不是由子类分配的内存。
    如果确实需要将父类指针转换为子类指针，可以使用 std::dynamic_pointer_cast 或者 std::static_pointer_cast，但是这些转换都需要明确的类型转换，而不是隐式转换。

    问：share_ptr可以从父类转换到子类吗？
    答：std::shared_ptr支持从父类指针转换为子类指针。这是因为std::shared_ptr使用引用计数来管理内存，允许多个指针共享同一块内存。
    因此，即使从父类指针转换为子类指针，也不会导致内存管理问题。
**/

class Target {
    public:
        virtual ~Target() = default;
        // Target(string s):str_(s) {}
        virtual string Request() const {
            return "Target: The default target's behavior.";
        }
};

class Adaptee {
    public:
        string SpecificRequest() const {
            return ".eetpadA eht fo roivaheb laicepS";
        }
};

class Adaptor : public Target {
    private:
        // Adaptee* adaptee_;
        unique_ptr<Adaptee> adaptee_;

    public:
        Adaptor(unique_ptr<Adaptee> ada) : adaptee_(std::move(ada)) {}
        string Request() const override {
            string To_reverse_str = adaptee_->SpecificRequest();
            std::reverse(To_reverse_str.begin(),To_reverse_str.end());
            cout<< "To_reverse_str: " << To_reverse_str << endl;
            return "Adapter: (TRANSLATED) " + To_reverse_str;
        }
};

void ClientCode(const Target* target) {
    cout<< target->Request();
};


// void ClientCode(unique_ptr<Target> & target) {
//     cout<< target->Request();
// };


int main() {
    unique_ptr<Target> target = make_unique<Target>();
    ClientCode(target.get());
    // ClientCode(target);

    std::cout << "\n\n";

    unique_ptr<Adaptee> adaptee = make_unique<Adaptee>();
    // Adaptee* adaptee = new Adaptee();

    std::cout << "Client: The Adaptee class has a weird interface. See, I don't understand it:\n";
    std::cout << "Adaptee: " << adaptee -> SpecificRequest();
    std::cout << "\n\n";
    std::cout << "Client: But I can work with it via the Adapter:\n";

    unique_ptr<Adaptor> adaptor = make_unique<Adaptor>(std::move(adaptee));
    ClientCode(adaptor.get());
    // ClientCode(adaptor);

    std::cout << "\n";

    // delete adaptee;

    return 0;
}