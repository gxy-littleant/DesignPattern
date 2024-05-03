#include <iostream>
#include <memory>

// Shape 接口
class Shape {
public:
    virtual std::unique_ptr<Shape> clone() const = 0;
    virtual void draw() const = 0;
};

// Circle 类
class Circle : public Shape {
public:
    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Circle>(*this);
    }
    void draw() const override {
        std::cout << "Drawing a circle." << std::endl;
    }
};

// Rectangle 类
class Rectangle : public Shape {
public:
    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Rectangle>(*this);
    }
    void draw() const override {
        std::cout << "Drawing a rectangle." << std::endl;
    }
};

// Triangle 类
class Triangle : public Shape {
public:
    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Triangle>(*this);
    }
    void draw() const override {
        std::cout << "Drawing a triangle." << std::endl;
    }
};

int main() {
    // 创建一个原型 Circle
    std::unique_ptr<Shape> circlePrototype = std::make_unique<Circle>();

    // 使用原型创建新对象
    std::unique_ptr<Shape> shape1 = circlePrototype->clone();
    std::unique_ptr<Shape> shape2 = circlePrototype->clone();

    // 绘制形状
    shape1->draw();
    shape2->draw();

    return 0;
}

// 一个常见的例子是在图形设计软件中，用户可以创建不同类型的形状，例如圆形、矩形、三角形等。假设我们要实现一个图形设计软件，用户可以在画布上创建各种形状，并且可以拖动、旋转、缩放这些形状。

// 在这个例子中，对象类型不确定，因为用户可以在运行时选择要创建的形状类型。我们可以使用原型模式来解决这个问题。

// 具体地，我们可以定义一个 Shape 接口，其中包含一个 clone 方法，用于复制对象。然后，我们可以实现不同类型的形状类，如 Circle、Rectangle 和 Triangle，这些类都实现了 Shape 接口，

// 并且在 clone 方法中返回自身的副本。


// 在这个例子中，Shape 接口定义了 clone 方法，Circle、Rectangle 和 Triangle 类都实现了该接口，
// 并在 clone 方法中返回自身的副本。通过使用原型模式，我们可以根据用户的选择动态创建不同类型的形状对象，而无需提前知道其具体类型。

// 所谓无需提前知道具体类型，是因为能创建的类型都已经继承了 Shape 这个基类 ，因此克隆的时候输入什么类型均可（只要是实现过基类clone接口的即可）