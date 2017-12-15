#include <gmock/gmock.h>
#include "figshare_gateway.hh"
#include "responses.hh"
#include "upload_command.hh"

using namespace testing;

class Driver {
public:
    Driver(FigshareGateway* gateway) : gateway(gateway) { }

    void handlePart(const FileInfo sourceFile, const FilePart partSpec) const;

private:
    FigshareGateway* gateway;
};

TEST(DriverTest, ActsAsIExpect) {
    // We want to check several interactions that are side effecting.
    // For instance, it's pretty obvious that putUpload should be called once
    // by this code.
    // Luckily, FigshareGateway is already an interface.

    MockFigshareGateway gateway;
    Driver driver(&gateway);

    EXPECT_CALL(gateway, putUpload(_)).Times(AtLeast(1));
    
    ASSERT_THAT(2 + 2, Eq(4));
}


