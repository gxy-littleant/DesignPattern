#include<iostream>
#include <stdio.h>
#include <string>
#include <memory>
using namespace std;


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

class Factory {
    public:
        virtual Car * createCar(string name) = 0;
};

class BmwFactory : public Factory {
    public:
        Car * createCar(string name) {
            return new Bmw(name);
        }
};

class AudiFactory : public Factory {
    public:
        Car * createCar(string name) {
            return new Audi(name);
        }
};


int main()
{
	unique_ptr<Factory> bmwfac(new BmwFactory());
    unique_ptr<Factory> audifac(new AudiFactory());
	unique_ptr<Car> p1(bmwfac->createCar("x6"));
	unique_ptr<Car> p2(audifac->createCar("a8"));

	p1->show();
	p2->show();

	return 0;
}
