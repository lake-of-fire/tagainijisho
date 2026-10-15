find_package(Qt6 REQUIRED COMPONENTS Test)
add_executable(lookup-url-test LookupUrlTest.cc
               ../src/gui/LookupUrl.cc ../src/gui/LookupApplication.cc)
target_include_directories(lookup-url-test PRIVATE ../src)
target_link_libraries(lookup-url-test PRIVATE Qt::Widgets Qt::Test)
add_test(NAME lookup-url COMMAND lookup-url-test)
set_tests_properties(lookup-url PROPERTIES ENVIRONMENT "QT_QPA_PLATFORM=offscreen")
