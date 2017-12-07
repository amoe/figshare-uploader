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

env.Program(
    target='unit_tests',
    source=[
        "article_type_mapper_test.cc",
        "category_test.cc",
        "fake_qt_core_application.cc",
        "stubs.cc",
        "view.cc",
        "test_harness.cc",
        "md5_test.cc",
        "mapper_test.cc",
        "xlsx.cc",
        "test_utility.cc",
        "integration_tests.cc",
        gtest_all_path, gmock_all_path
    ]
)

env.Program(
    target='main',
    source=["main.cc", "view.cc", "presenter.cc"]
)

# env.Program(
#     target='category_demo',
#     source=['category_demo.cc']
# )
