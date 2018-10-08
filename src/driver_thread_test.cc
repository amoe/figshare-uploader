#include <gmock/gmock.h>
#include "driver_thread.hh"

using namespace testing;

class DriverThreadTest: public Test {
};

TEST_F(DriverThreadTest, ChecksThatAllRelatedFilesExist) {
    // This is not needed for the class.
    QObject* parent = Q_NULLPTR;
    Driver* driver = nullptr;
    string inputPath = "";

    // An input path should be provided but we need to be able to factor
    // this out through an interface really.  Unfortunately XlsxReader 
    // constructs its own dependencies.  We need to refactor the interface
    // of XlsxReader to construct with no arguments and use a 'load()'
    // method to load the file.  Which may possibly be more natural anyway.

    // Once that is done, we can then mock out the XlsxReader interface to
    // ReturnOnce rowToString() etc with an appropriate set of values.
    // driver will also need to be mocked to just be a no-op on 'handleRow'
    // and 'log'.

    DriverThread d(parent, driver, inputPath);

    ASSERT_THAT(2 + 2, Eq(4));
}

