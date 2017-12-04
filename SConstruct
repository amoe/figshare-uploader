googletest_framework_root = "./ext/googletest-release-1.8.0"

googletest_include_paths = [
    googletest_framework_root + "/googletest",
    googletest_framework_root + "/googletest/include",
    googletest_framework_root + "/googlemock",
    googletest_framework_root + "/googlemock/include"
]

gtest_all_path = googletest_framework_root + "/googletest/src/gtest-all.cc"
gmock_all_path = googletest_framework_root + "/googlemock/src/gmock-all.cc"

env = Environment(CPPPATH=googletest_include_paths)

env.Program(
    target='unit_tests',
    source=["test_harness.cc", gtest_all_path, gmock_all_path],
    LIBS=['pthread']
)

