#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class AbstractProduct
{
    public:
        virtual ~AbstractProduct() {};
        virtual void setDisplay(string display) = 0;
        virtual void setHost(string host) = 0;
        virtual void setKeyBoard(string KeyBoard) = 0;
        virtual void setMouse(string mouse) = 0;
        virtual void show() = 0;
};

class Computer : public AbstractProduct
{
    public:
        ~Computer() {}
        void setDisplay(string display)
        {
            m_vec.emplace_back(display);
        }
        void setHost(string host)
        {
            m_vec.emplace_back(host);
        }
        void setKeyBoard(string KeyBoard)
        {
            m_vec.emplace_back(KeyBoard);
        }
        void setMouse(string mouse)
        {
            m_vec.emplace_back(mouse);
        }
        void show()
        {
            cout << "----------组装电脑---------" << endl;
            for (auto& x : m_vec)
            {
                cout << x << endl;
            }
        }
    private:
        vector<string> m_vec;
};

class AbstractBuilder
{
    public:
        AbstractBuilder(): product(new Computer()) {};

        virtual ~AbstractBuilder() {}
        virtual void BuildDisplay(string display) = 0;
        virtual void BuildHost(string host) = 0;
        virtual void BuildKeyBoard(string KeyBoard) = 0;
        virtual void BuildMouse(string mouse) = 0;
        AbstractProduct* getProduct() {
            return product;
        }

    
    protected:
	    AbstractProduct* product;
};  

class ComputerBuilder : public AbstractBuilder
{
    public:
        ~ComputerBuilder() {};
        void BuildDisplay(string display)
	{
		product->setDisplay(display);
	}
	void BuildHost(string host)
	{
		product->setHost(host);
	}
	void BuildKeyBoard(string KeyBoard)
	{
		product->setKeyBoard(KeyBoard);
	}
	void BuildMouse(string mouse)
	{
		product->setMouse(mouse);
	}
};


class Director
{
    public:
        Director(AbstractBuilder* builder): m_builder(builder) {};
        ~Director() {}
        AbstractProduct* createComputer (string display, string host, string KeyBoard, string mouse) {
            m_builder->BuildDisplay(display);
            m_builder->BuildHost(host);
            m_builder->BuildKeyBoard(KeyBoard);
            m_builder->BuildMouse(mouse);
            return m_builder->getProduct();
        }

    private:
	    AbstractBuilder* m_builder;
};

int main() {

    // unique_ptr<AbstractBuilder> AbsComBuilder(new ComputerBuilder());
    // unique_ptr<Director> DirComputer(AbsComBuilder.get());

    AbstractBuilder* AbsComBuilder = new ComputerBuilder();
    Director* DirComputer = new Director{AbsComBuilder};
    AbstractProduct* ComputerPro = DirComputer->createComputer("联想显示器", "外星人主机", "雷蛇键盘", "罗技鼠标");
    ComputerPro->show();

    delete AbsComBuilder;
	delete DirComputer;
	delete ComputerPro;

    return 0;
}