# Install script for directory: E:/MIME/third_part/muduo/muduo/base

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/muduo")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/MIME/third_part/muduo/cmake-build-debug/lib/libmuduo_base.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/muduo/base" TYPE FILE FILES
    "E:/MIME/third_part/muduo/muduo/base/AsyncLogging.h"
    "E:/MIME/third_part/muduo/muduo/base/Atomic.h"
    "E:/MIME/third_part/muduo/muduo/base/BlockingQueue.h"
    "E:/MIME/third_part/muduo/muduo/base/BoundedBlockingQueue.h"
    "E:/MIME/third_part/muduo/muduo/base/Condition.h"
    "E:/MIME/third_part/muduo/muduo/base/CountDownLatch.h"
    "E:/MIME/third_part/muduo/muduo/base/CurrentThread.h"
    "E:/MIME/third_part/muduo/muduo/base/Date.h"
    "E:/MIME/third_part/muduo/muduo/base/Exception.h"
    "E:/MIME/third_part/muduo/muduo/base/FileUtil.h"
    "E:/MIME/third_part/muduo/muduo/base/GzipFile.h"
    "E:/MIME/third_part/muduo/muduo/base/LogFile.h"
    "E:/MIME/third_part/muduo/muduo/base/LogStream.h"
    "E:/MIME/third_part/muduo/muduo/base/Logging.h"
    "E:/MIME/third_part/muduo/muduo/base/Mutex.h"
    "E:/MIME/third_part/muduo/muduo/base/ProcessInfo.h"
    "E:/MIME/third_part/muduo/muduo/base/Singleton.h"
    "E:/MIME/third_part/muduo/muduo/base/StringPiece.h"
    "E:/MIME/third_part/muduo/muduo/base/Thread.h"
    "E:/MIME/third_part/muduo/muduo/base/ThreadLocal.h"
    "E:/MIME/third_part/muduo/muduo/base/ThreadLocalSingleton.h"
    "E:/MIME/third_part/muduo/muduo/base/ThreadPool.h"
    "E:/MIME/third_part/muduo/muduo/base/TimeZone.h"
    "E:/MIME/third_part/muduo/muduo/base/Timestamp.h"
    "E:/MIME/third_part/muduo/muduo/base/Types.h"
    "E:/MIME/third_part/muduo/muduo/base/WeakCallback.h"
    "E:/MIME/third_part/muduo/muduo/base/copyable.h"
    "E:/MIME/third_part/muduo/muduo/base/noncopyable.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("E:/MIME/third_part/muduo/cmake-build-debug/muduo/base/tests/cmake_install.cmake")

endif()

