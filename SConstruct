
googletest_framework_root = "./ext/googletest-release-1.8.0"

googletest_include_paths = [
    googletest_framework_root + "/googletest",
    googletest_framework_root + "/googletest/include",
    googletest_framework_root + "/googlemock",
    googletest_framework_root + "/googlemock/include"
]

gtest_all_path = googletest_framework_root + "/googletest/src/gtest-all.cc"
gmock_all_path = googletest_framework_root + "/googlemock/src/gmock-all.cc"

env = Environment(
    tools=['default', 'qt5'],
    QT5DIR='/usr',
    CPPPATH=googletest_include_paths,
    
)
env['QT5_DEBUG'] = 1

env.EnableQt5Modules(['QtCore', 'QtWidgets', 'QtNetwork'])
env.Append(CCFLAGS=['-fPIC', '-std=c++11'])
env.Append(
    LIBS=[
        'pthread',
        'xlnt'
    ]
)

gtest = env.Object(gtest_all_path)
gmock = env.Object(gmock_all_path)
test_harness = env.Object("test_harness.cc")
test_utility = env.Object("test_utility.cc")

env.Program(
    target='unit_tests',
    source=[
        "requests.cc",
#        "figshare_gateway_test.cc",
        "license_test.cc",
        "article_type_mapper.cc",
        "article_type_mapper_test.cc",
        "category_test.cc",
        "stubs.cc",
        "view.cc",
        "md5_test.cc",
        "mapper_test.cc",
        "xlsx.cc",
        test_harness, test_utility, gtest, gmock
    ]
)

integration_environment = env.Clone()
integration_environment.Append(CPPPATH=".")

integration_tests = Glob("./test/integration/*.cc")
integration_tests.extend(
    [test_harness, test_utility,  gtest, gmock]
)

integration_environment.Program(
    target='integration_tests',
    source=integration_tests,
)

env.Program(
    target='main',
    source=["main.cc", "view.cc", "presenter.cc"]
)

# env.Program(
#     target='category_demo',
#     source=['category_demo.cc']
# )
