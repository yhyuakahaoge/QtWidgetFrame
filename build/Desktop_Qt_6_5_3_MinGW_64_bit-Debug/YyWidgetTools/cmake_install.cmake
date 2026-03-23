# Install script for directory: D:/dev3/YyWidgetTools/YyWidgetTools

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "D:/dev3/YyWidgetTools/Install")
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

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "D:/QT/Tools/mingw1120_64/bin/objdump.exe")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/YyWidgetTools/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/dev3/YyWidgetTools/build/Desktop_Qt_6_5_3_MinGW_64_bit-Debug/YyWidgetTools/libYyWidgetTools.dll.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/YyWidgetTools/bin" TYPE SHARED_LIBRARY FILES "D:/dev3/YyWidgetTools/build/Desktop_Qt_6_5_3_MinGW_64_bit-Debug/YyWidgetTools/YyWidgetTools.dll")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/YyWidgetTools/bin/YyWidgetTools.dll" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/YyWidgetTools/bin/YyWidgetTools.dll")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "D:/QT/Tools/mingw1120_64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/YyWidgetTools/bin/YyWidgetTools.dll")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "D:/dev3/YyWidgetTools/Install/YyWidgetToolsExample/YyWidgetTools.dll")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "D:/dev3/YyWidgetTools/Install/YyWidgetToolsExample" TYPE SHARED_LIBRARY FILES "D:/dev3/YyWidgetTools/build/Desktop_Qt_6_5_3_MinGW_64_bit-Debug/YyWidgetTools/YyWidgetTools.dll")
  if(EXISTS "$ENV{DESTDIR}/D:/dev3/YyWidgetTools/Install/YyWidgetToolsExample/YyWidgetTools.dll" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/D:/dev3/YyWidgetTools/Install/YyWidgetToolsExample/YyWidgetTools.dll")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "D:/QT/Tools/mingw1120_64/bin/strip.exe" "$ENV{DESTDIR}/D:/dev3/YyWidgetTools/Install/YyWidgetToolsExample/YyWidgetTools.dll")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/YyWidgetTools/include" TYPE FILE FILES
    "D:/dev3/YyWidgetTools/YyWidgetTools/YyAppBar.h"
    "D:/dev3/YyWidgetTools/YyWidgetTools/YyDef.h"
    "D:/dev3/YyWidgetTools/YyWidgetTools/YyProperty.h"
    "D:/dev3/YyWidgetTools/YyWidgetTools/YySingleton.h"
    "D:/dev3/YyWidgetTools/YyWidgetTools/YyWindow.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/YyWidgetTools/lib/cmake/YyWidgetToolsTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/YyWidgetTools/lib/cmake/YyWidgetToolsTargets.cmake"
         "D:/dev3/YyWidgetTools/build/Desktop_Qt_6_5_3_MinGW_64_bit-Debug/YyWidgetTools/CMakeFiles/Export/afbaa3439801545cfa8777128838fbd3/YyWidgetToolsTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/YyWidgetTools/lib/cmake/YyWidgetToolsTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/YyWidgetTools/lib/cmake/YyWidgetToolsTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/YyWidgetTools/lib/cmake" TYPE FILE FILES "D:/dev3/YyWidgetTools/build/Desktop_Qt_6_5_3_MinGW_64_bit-Debug/YyWidgetTools/CMakeFiles/Export/afbaa3439801545cfa8777128838fbd3/YyWidgetToolsTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/YyWidgetTools/lib/cmake" TYPE FILE FILES "D:/dev3/YyWidgetTools/build/Desktop_Qt_6_5_3_MinGW_64_bit-Debug/YyWidgetTools/CMakeFiles/Export/afbaa3439801545cfa8777128838fbd3/YyWidgetToolsTargets-debug.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/YyWidgetTools/lib/cmake" TYPE FILE FILES
    "D:/dev3/YyWidgetTools/build/Desktop_Qt_6_5_3_MinGW_64_bit-Debug/YyWidgetTools/YyWidgetToolsConfig.cmake"
    "D:/dev3/YyWidgetTools/build/Desktop_Qt_6_5_3_MinGW_64_bit-Debug/YyWidgetTools/YyWidgetToolsConfigVersion.cmake"
    )
endif()

