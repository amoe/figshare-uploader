#include <iostream>
#include <gmock/gmock.h>
#include <QString>

using ::testing::Eq;

class QtWrapper {
public:
    static std::string toUpperCase(const std::string& input) {
        QString myString = QString::fromStdString(input);
        return myString.toUpper().toStdString();
    }; 
};

TEST(QtWrapper, CanUseQtClasses) {
    ASSERT_THAT(QtWrapper::toUpperCase("hello world"), Eq("HELLO WORLD"));
}


int main(int argc, char **argv) {
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
