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

print("Prog emitter:", env['PROGEMITTER'])
print("Program is" + repr(env['BUILDERS']['Program'].emitter))


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
        "settings.cc",
        "file_info_test.cc",
        "file_info.cc",
        "requests.cc",
        "figshare_gateway_test.cc",
        "figshare_gateway.cc",
        "license_test.cc",
        "article_type_mapper.cc",
        "token_store.cc",
        "article_type_mapper_test.cc",
        "article_mapper.cc",
        "path_extractor_test.cc",
        "path_extractor.cc",
        "category_test.cc",
        "category_mapper.cc",
        "stubs.cc",
        "md5_test.cc",
        "file_spec_generator.cc",
        "mapper_test.cc",
        "xlsx_test.cc",
        "part_preparer_test.cc",
        "part_preparer.cc",
        "file_part.cc",
        "upload_command.cc",
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

env.Program(
    target='main',
    source=[
        "settings.cc",
        "main.cc", "view.cc", "presenter.cc", "run_upload_task.cc",
        "driver_thread.cc",
        "file_info.cc",
        "requests.cc",
        "figshare_gateway.cc",
        "article_type_mapper.cc",
        "article_mapper.cc",
        "category_mapper.cc",
        "file_spec_generator.cc",
        "token_store.cc",
        "part_preparer.cc",
        "file_part.cc",
        "upload_command.cc",
        "http_putter.cc",
        "upload_command_processor.cc",
        "http_getter.cc",
        "http_poster.cc",
        "xlsx.cc",
        "size_getter.cc",
        "upload_container_info.cc",
        "responses.cc",
        "driver.cc",
        "path_extractor.cc",
        "utility.cc"
    ]
)
