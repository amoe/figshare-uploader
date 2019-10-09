#include <gmock/gmock.h>
#include "raw_literals.hh"
#include "license_mapper.hh"

using ::testing::Eq;

TEST(LicenseMapper, MapsLicenseSuccessfully) {
    LicenseMapper mapper(raw_literals::licensesResponse);
    int licenseId = mapper.mapName("CC BY 4.0");

    ASSERT_THAT(licenseId, Eq(1));
}
