#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "sigc-3.0" for configuration ""
set_property(TARGET sigc-3.0 APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(sigc-3.0 PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libsigc-3.0.2.99.1.dylib"
  IMPORTED_SONAME_NOCONFIG "@rpath/libsigc-3.0.0.dylib"
  )

list(APPEND _IMPORT_CHECK_TARGETS sigc-3.0 )
list(APPEND _IMPORT_CHECK_FILES_FOR_sigc-3.0 "${_IMPORT_PREFIX}/lib/libsigc-3.0.2.99.1.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
