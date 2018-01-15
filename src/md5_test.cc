#include <gmock/gmock.h>
#include "md5.hh"

using std::string;
using ::testing::Eq;

TEST(MD5Calculator, CanUseByteArrayDevice) {
    MD5Calculator theCalc;

    QString data = "The quick brown fox jumps over the lazy dog";
    QByteArray data2 = data.toUtf8();

    DataSource* ds2 = new ByteArrayDataSource(data2);
    string result2 = theCalc.getMD5(ds2);

    // This is a well known result
    ASSERT_THAT(result2, Eq("9e107d9d372bb6826bd81d3542a419d6"));
}
