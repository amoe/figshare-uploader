#include <gmock/gmock.h>
#include <iostream>

using namespace testing;

// turtle interface

class Turtle {
public:
    virtual ~Turtle() {}
    virtual void penUp() = 0;
    virtual void penDown() = 0;
    virtual void forward(int distance) = 0;
    virtual void turn(int degrees) = 0;
    virtual void goTo(int x, int y) = 0;
    virtual int getX() const = 0;
    virtual int getY() const = 0;
};

class FakeTurtle : public Turtle {
public:
    MOCK_METHOD0(penUp, void());
    MOCK_METHOD0(penDown, void());
    MOCK_METHOD1(forward, void(int distance));
    MOCK_METHOD1(turn, void(int degrees));
    MOCK_METHOD2(goTo, void(int x, int y));

    MOCK_CONST_METHOD0(getX, int());
    MOCK_CONST_METHOD0(getY, int());
};

class Painter {
public:
    Painter(Turtle* t) : t(t) { }
    void drawCircle(int x, int y, int r);

private:
    Turtle* t;
};

void Painter::drawCircle(int x, int y, int r) {
    std::cout << "Not doing anything" << std::endl;
    t->penDown();
}

TEST(TurtleTest, CanDrawSomething) {
    FakeTurtle turtle;

// Actual function call count doesn't match EXPECT_CALL(turtle, penDown())...
//          Expected: to be called at least once
//            Actual: never called - unsatisfied and active

    EXPECT_CALL(turtle, penDown()).Times(AtLeast(1));

    Painter painter(&turtle);

    painter.drawCircle(1, 1, 1);

    // Calls are checked at time of destruction of the mock.
}
