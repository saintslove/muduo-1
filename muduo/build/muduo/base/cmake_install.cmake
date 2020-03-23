# Install script for directory: F:/muduo/muduo/muduo/base

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/muduo")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "F:/muduo/muduo/build/lib/Debug/muduo_base.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "F:/muduo/muduo/build/lib/Release/muduo_base.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "F:/muduo/muduo/build/lib/MinSizeRel/muduo_base.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "F:/muduo/muduo/build/lib/RelWithDebInfo/muduo_base.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/muduo/base" TYPE FILE FILES
    "F:/muduo/muduo/muduo/base/AsyncLogging.h"
    "F:/muduo/muduo/muduo/base/Atomic.h"
    "F:/muduo/muduo/muduo/base/BlockingQueue.h"
    "F:/muduo/muduo/muduo/base/BoundedBlockingQueue.h"
    "F:/muduo/muduo/muduo/base/Condition.h"
    "F:/muduo/muduo/muduo/base/CountDownLatch.h"
    "F:/muduo/muduo/muduo/base/CurrentThread.h"
    "F:/muduo/muduo/muduo/base/Date.h"
    "F:/muduo/muduo/muduo/base/Exception.h"
    "F:/muduo/muduo/muduo/base/FileUtil.h"
    "F:/muduo/muduo/muduo/base/GzipFile.h"
    "F:/muduo/muduo/muduo/base/LogFile.h"
    "F:/muduo/muduo/muduo/base/LogStream.h"
    "F:/muduo/muduo/muduo/base/Logging.h"
    "F:/muduo/muduo/muduo/base/Mutex.h"
    "F:/muduo/muduo/muduo/base/ProcessInfo.h"
    "F:/muduo/muduo/muduo/base/Singleton.h"
    "F:/muduo/muduo/muduo/base/StringPiece.h"
    "F:/muduo/muduo/muduo/base/Thread.h"
    "F:/muduo/muduo/muduo/base/ThreadLocal.h"
    "F:/muduo/muduo/muduo/base/ThreadLocalSingleton.h"
    "F:/muduo/muduo/muduo/base/ThreadPool.h"
    "F:/muduo/muduo/muduo/base/TimeZone.h"
    "F:/muduo/muduo/muduo/base/Timestamp.h"
    "F:/muduo/muduo/muduo/base/Types.h"
    "F:/muduo/muduo/muduo/base/WeakCallback.h"
    "F:/muduo/muduo/muduo/base/copyable.h"
    "F:/muduo/muduo/muduo/base/noncopyable.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("F:/muduo/muduo/build/muduo/base/tests/cmake_install.cmake")

endif()

