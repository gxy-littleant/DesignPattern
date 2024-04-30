#include<iostream>
#include <stdio.h>
#include <string>
#include <memory>
using namespace std;

enum Cartype
{
	BMW, AUDI
};

class Car 
{
    public:
        Car(string name) :_name(name) {}
        virtual void show() = 0;
    
    protected:
        string _name;
};

class Bmw: public Car {
	public:
		Bmw(string name) : Car(name) {}
		void show() {
			cout<<"获取了一辆宝马车: "<<_name<<endl;
		} 
};

class Audi : public Car {
	public:
		Audi(string name) : Car(name) {}
		void show () {
			cout<<"获取了一辆奥迪车: "<<_name<<endl;
		}
};

class SimpleFactory {
    public :
        Car * createCar(Cartype ct) {
            switch (ct)
            {
            case BMW:
                return new Bmw("x6");
            case AUDI:
                return new Audi("a8");
            default:
                cout << "传入参数错误: "<< ct << endl;
            }
            return nullptr;
        }
};



int main()
{
	unique_ptr<SimpleFactory> fac(new SimpleFactory());
	unique_ptr<Car> p1(fac->createCar(BMW));
	unique_ptr<Car> p2(fac->createCar(AUDI));

	p1->show();
	p2->show();

	return 0;
}
