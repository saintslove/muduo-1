# CMake generated Testfile for 
# Source directory: F:/muduo/muduo/muduo/net/tests
# Build directory: F:/muduo/muduo/build/muduo/net/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(timerqueue_unittest "F:/muduo/muduo/build/bin/Debug/timerqueue_unittest.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(timerqueue_unittest "F:/muduo/muduo/build/bin/Release/timerqueue_unittest.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(timerqueue_unittest "F:/muduo/muduo/build/bin/MinSizeRel/timerqueue_unittest.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(timerqueue_unittest "F:/muduo/muduo/build/bin/RelWithDebInfo/timerqueue_unittest.exe")
else()
  add_test(timerqueue_unittest NOT_AVAILABLE)
endif()
