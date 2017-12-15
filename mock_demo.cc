#include <gmock/gmock.h>

using namespace testing;

// turtle interface

class Turtle {
    virtual ~Turtle() {}
    virtual void penUp() = 0;
    virtual void penDown() = 0;
    virtual void forward(int distance) = 0;
    virtual void turn(int degrees) = 0;
    virtual void goTo(int x, int y) = 0;
    virtual int getX() const = 0;
    virtual int getY() const = 0;
};

TEST(TurtleTest, ActsAsIExpect) {
    ASSERT_THAT(2 + 2, Eq(4));
}

