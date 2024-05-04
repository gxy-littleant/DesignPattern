#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

// 有问题：为什么在第二个ClientCode函数中调用的不是 adaptee ？ 而是默认的target？

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
        string Request() {
            string To_reverse_str = adaptee_->SpecificRequest();
            std::reverse(To_reverse_str.begin(),To_reverse_str.end());
            cout<< "To_reverse_str: " << To_reverse_str << endl;
            return "Adapter: (TRANSLATED) " + To_reverse_str;
        }
};

void ClientCode(unique_ptr<Target> const & target) {
    cout<< target->Request();
};

int main() {
    // Target * target = new Target();
    unique_ptr<Target> target = make_unique<Target>();
    ClientCode(target);
    std::cout << "\n\n";

    unique_ptr<Adaptee> adaptee = make_unique<Adaptee>();
    std::cout << "Client: The Adaptee class has a weird interface. See, I don't understand it:\n";
    std::cout << "Adaptee: " << adaptee->SpecificRequest();
    std::cout << "\n\n";
    std::cout << "Client: But I can work with it via the Adapter:\n";

    unique_ptr<Target> adaptor = make_unique<Adaptor>(std::move(adaptee));
    ClientCode(adaptor);
    std::cout << "\n";

    return 0;
}