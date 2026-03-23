# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "YyWidgetTools\\CMakeFiles\\YyWidgetTools_autogen.dir\\AutogenUsed.txt"
  "YyWidgetTools\\CMakeFiles\\YyWidgetTools_autogen.dir\\ParseCache.txt"
  "YyWidgetTools\\YyWidgetTools_autogen"
  "YyWidgetToolsExample\\CMakeFiles\\YyWidgetToolsExample_autogen.dir\\AutogenUsed.txt"
  "YyWidgetToolsExample\\CMakeFiles\\YyWidgetToolsExample_autogen.dir\\ParseCache.txt"
  "YyWidgetToolsExample\\YyWidgetToolsExample_autogen"
  )
endif()
