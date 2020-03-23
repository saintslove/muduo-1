# Install script for directory: /opt/qiwang30/muduo/muduo/muduo/base

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/opt/qiwang30/muduo/muduo/cmake-build-release/lib/libmuduo_base.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/muduo/base" TYPE FILE FILES
    "/opt/qiwang30/muduo/muduo/muduo/base/AsyncLogging.h"
    "/opt/qiwang30/muduo/muduo/muduo/base/Atomic.h"
    "/opt/qiwang30/muduo/muduo/muduo/base/BlockingQueue.h"
    "/opt/qiwang30/muduo/muduo/muduo/base/BoundedBlockingQueue.h"
    "/opt/qiwang30/muduo/muduo/muduo/base/Condition.h"
    "/opt/qiwang30/muduo/muduo/muduo/base/CountDownLatch.h"
    "/opt/qiwang30/muduo/muduo/muduo/base/CurrentThread.h"
    "/opt/qiwang30/muduo/muduo/muduo/base/Date.h"
    "/opt/qiwang30/muduo/muduo/muduo/base/Exception.h"
    "/opt/qiwang30/muduo/muduo/muduo/base/FileUtil.h"
    "/opt/qiwang30/muduo/muduo/muduo/base/GzipFile.h"
    "/opt/qiwang30/muduo/muduo/muduo/base/LogFile.h"
    "/opt/qiwang30/muduo/muduo/muduo/base/LogStream.h"
    "/opt/qiwang30/muduo/muduo/muduo/base/Logging.h"
    "/opt/qiwang30/muduo/muduo/muduo/base/Mutex.h"
    "/opt/qiwang30/muduo/muduo/muduo/base/ProcessInfo.h"
    "/opt/qiwang30/muduo/muduo/muduo/base/Singleton.h"
    "/opt/qiwang30/muduo/muduo/muduo/base/StringPiece.h"
    "/opt/qiwang30/muduo/muduo/muduo/base/Thread.h"
    "/opt/qiwang30/muduo/muduo/muduo/base/ThreadLocal.h"
    "/opt/qiwang30/muduo/muduo/muduo/base/ThreadLocalSingleton.h"
    "/opt/qiwang30/muduo/muduo/muduo/base/ThreadPool.h"
    "/opt/qiwang30/muduo/muduo/muduo/base/TimeZone.h"
    "/opt/qiwang30/muduo/muduo/muduo/base/Timestamp.h"
    "/opt/qiwang30/muduo/muduo/muduo/base/Types.h"
    "/opt/qiwang30/muduo/muduo/muduo/base/WeakCallback.h"
    "/opt/qiwang30/muduo/muduo/muduo/base/copyable.h"
    "/opt/qiwang30/muduo/muduo/muduo/base/noncopyable.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/opt/qiwang30/muduo/muduo/cmake-build-release/muduo/base/tests/cmake_install.cmake")

endif()

