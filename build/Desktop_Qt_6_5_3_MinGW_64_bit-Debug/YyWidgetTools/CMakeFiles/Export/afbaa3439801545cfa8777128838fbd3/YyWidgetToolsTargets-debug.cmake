#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "YyWidgetTools" for configuration "Debug"
set_property(TARGET YyWidgetTools APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(YyWidgetTools PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/YyWidgetTools/lib/libYyWidgetTools.dll.a"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/YyWidgetTools/bin/YyWidgetTools.dll"
  )

list(APPEND _cmake_import_check_targets YyWidgetTools )
list(APPEND _cmake_import_check_files_for_YyWidgetTools "${_IMPORT_PREFIX}/YyWidgetTools/lib/libYyWidgetTools.dll.a" "${_IMPORT_PREFIX}/YyWidgetTools/bin/YyWidgetTools.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
