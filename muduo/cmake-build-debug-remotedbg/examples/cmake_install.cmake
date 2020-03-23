# Install script for directory: /opt/qiwang30/muduo/muduo/examples

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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/opt/qiwang30/muduo/muduo/cmake-build-debug-remotedbg/examples/ace/ttcp/cmake_install.cmake")
  include("/opt/qiwang30/muduo/muduo/cmake-build-debug-remotedbg/examples/asio/chat/cmake_install.cmake")
  include("/opt/qiwang30/muduo/muduo/cmake-build-debug-remotedbg/examples/asio/tutorial/cmake_install.cmake")
  include("/opt/qiwang30/muduo/muduo/cmake-build-debug-remotedbg/examples/fastcgi/cmake_install.cmake")
  include("/opt/qiwang30/muduo/muduo/cmake-build-debug-remotedbg/examples/filetransfer/cmake_install.cmake")
  include("/opt/qiwang30/muduo/muduo/cmake-build-debug-remotedbg/examples/hub/cmake_install.cmake")
  include("/opt/qiwang30/muduo/muduo/cmake-build-debug-remotedbg/examples/idleconnection/cmake_install.cmake")
  include("/opt/qiwang30/muduo/muduo/cmake-build-debug-remotedbg/examples/maxconnection/cmake_install.cmake")
  include("/opt/qiwang30/muduo/muduo/cmake-build-debug-remotedbg/examples/memcached/client/cmake_install.cmake")
  include("/opt/qiwang30/muduo/muduo/cmake-build-debug-remotedbg/examples/memcached/server/cmake_install.cmake")
  include("/opt/qiwang30/muduo/muduo/cmake-build-debug-remotedbg/examples/multiplexer/cmake_install.cmake")
  include("/opt/qiwang30/muduo/muduo/cmake-build-debug-remotedbg/examples/netty/discard/cmake_install.cmake")
  include("/opt/qiwang30/muduo/muduo/cmake-build-debug-remotedbg/examples/netty/echo/cmake_install.cmake")
  include("/opt/qiwang30/muduo/muduo/cmake-build-debug-remotedbg/examples/netty/uptime/cmake_install.cmake")
  include("/opt/qiwang30/muduo/muduo/cmake-build-debug-remotedbg/examples/pingpong/cmake_install.cmake")
  include("/opt/qiwang30/muduo/muduo/cmake-build-debug-remotedbg/examples/roundtrip/cmake_install.cmake")
  include("/opt/qiwang30/muduo/muduo/cmake-build-debug-remotedbg/examples/shorturl/cmake_install.cmake")
  include("/opt/qiwang30/muduo/muduo/cmake-build-debug-remotedbg/examples/simple/cmake_install.cmake")
  include("/opt/qiwang30/muduo/muduo/cmake-build-debug-remotedbg/examples/socks4a/cmake_install.cmake")
  include("/opt/qiwang30/muduo/muduo/cmake-build-debug-remotedbg/examples/sudoku/cmake_install.cmake")
  include("/opt/qiwang30/muduo/muduo/cmake-build-debug-remotedbg/examples/twisted/finger/cmake_install.cmake")
  include("/opt/qiwang30/muduo/muduo/cmake-build-debug-remotedbg/examples/wordcount/cmake_install.cmake")
  include("/opt/qiwang30/muduo/muduo/cmake-build-debug-remotedbg/examples/zeromq/cmake_install.cmake")

endif()

