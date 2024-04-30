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

class Light 
{
    public:
        virtual void show() = 0;
};

class BmwLight: public Light 
{
    public:
        void show() {
            cout << "BMW light!" << endl;
        }
};

class AudiLight: public Light 
{
    public:
        void show() {
            cout << "Audi light!" << endl;
        }
};

class AbstractFactory {
    public:
        virtual Car* createCar(string name) = 0; 
        virtual Light* createLight() = 0; 
};

class BmwFactory : public AbstractFactory
{
    public:
        Car* createCar(string name) {
            return new Bmw(name);
        }

        Light* createLight() {
            return new BmwLight();
        }
};

class AudiFactory : public AbstractFactory
{
    public:
        Car* createCar(string name) {
            return new Audi(name);
        }

        Light* createLight() {
            return new AudiLight();
        }
};

int main()
{
	unique_ptr<AbstractFactory> bmwfac(new BmwFactory());
    unique_ptr<AbstractFactory> audifac(new AudiFactory());
	unique_ptr<Car> bmwcar(bmwfac->createCar("x6"));
    unique_ptr<Car> audicar(audifac->createCar("a8"));
	unique_ptr<Light> bmwlight(bmwfac->createLight());
    unique_ptr<Light> audilight(audifac->createLight());

	bmwcar->show();
    bmwlight->show();

	audicar->show();
    audilight->show();

	return 0;
}
