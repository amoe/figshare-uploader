#include <gmock/gmock.h>
#include "requests.hh"
#include "test_utility.hh"
#include "raw_literals.hh"
#include "test_vocabulary.hh"

using std::string;

TEST(RequestTest, UploadCreationRequestSerializesCorrectly) {
    UploadCreationRequest request("nonesuch.png",  "9e107d9d372bb6826bd81d3542a419d6", 1234000);

    string serializedResult = request.toJson();

    ASSERT_THAT(
        deserialize(serializedResult),
        Eq(deserialize(raw_literals::serializedUploadCreationRequest))
    );
}



