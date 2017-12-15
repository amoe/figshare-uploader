import os

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
env['ENV']['TERM'] = os.environ['TERM']

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
utility = env.Object("utility.cc")
http_getter = env.Object("http_getter.cc")
http_poster = env.Object("http_poster.cc")

env.Program(
    target='unit_tests',
    source=[
        "file_info_test.cc",
        "file_info.cc",
        "requests.cc",
        "figshare_gateway_test.cc",
        "figshare_gateway.cc",
        "license_test.cc",
        "article_type_mapper.cc",
        "article_type_mapper_test.cc",
        "article_mapper.cc",
        "category_test.cc",
        "category_mapper.cc",
        "stubs.cc",
        "view.cc",
        "md5_test.cc",
        "mapper_test.cc",
        "xlsx_test.cc",
        "part_preparer_test.cc",
        "part_preparer.cc",
        "file_part.cc",
        "upload_command.cc",
        "io_slicer.cc",
        "io_slicer_test.cc",
        "http_putter.cc",
        "upload_command_processor.cc",
        "upload_command_processor_test.cc",
        "fake_qt_core_application.cc",
        "http_getter.cc",
        "http_poster.cc",
        "http_getter_test.cc",
        "http_poster_test.cc",
        "xlsx.cc",
        "size_getter_integration_test.cc",
        "size_getter.cc",
        "requests_test.cc",
        "upload_container_info_test.cc",
        "upload_container_info.cc",
        "file_part_test.cc",
        "responses_test.cc",
        "responses.cc",
        "driver_test.cc",
        "driver.cc",
        "object_mother.cc",
        utility,
        test_harness, test_utility, gtest, gmock
    ]
)

integration_environment = env.Clone()
integration_environment.Append(CPPPATH=".")

integration_tests = Glob("./test/integration/*.cc")
integration_tests.extend(
    [http_getter, http_poster, utility]
)

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

# env.Program(
#     target='driver_demo',
#     source=[
#         "driver_demo.cc",
#         "xlsx.cc",
#         "article_type_mapper.cc",
#         "requests.cc",
#         "article_mapper.cc",
#         "utility.cc",
#         "http_poster.cc",
#         "figshare_gateway.cc",
#         "http_getter.cc",
#         "category_mapper.cc",
#         "size_getter.cc",
#         "upload_container_info.cc",
#         "file_part.cc",
#         "io_slicer.cc",
#         "part_preparer.cc",
#         "upload_command.cc",
#         "http_putter.cc",
#         "file_info.cc",
#         "responses.cc"
#     ]
# )



# env.Program(
#     target='test_logging',
#     source=[
#         "test_logging.cc",
#         "logging.cc"
#     ]
# )



# env.Program(
#     target='mock_demo',
#     source=[
#         'mock_demo.cc',
#         test_harness, gtest, gmock
#     ]
# )
