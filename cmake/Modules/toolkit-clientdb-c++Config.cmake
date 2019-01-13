SET(TARGET_OBJECT_SUFFIX toolkit-clientdb-c++)

IF (TOOLKIT_CLIENTDB_INCLUDE_DIR)
  # Already in cache, be silent
  SET(TOOLKIT_CLIENTDB_FIND_QUIETLY TRUE)
ENDIF (TOOLKIT_CLIENTDB_INCLUDE_DIR)

FIND_PATH(TOOLKIT_CLIENTDB_INCLUDE_DIR clientdb.hpp
  /usr/include/toolkit
  /usr/local/include/toolkit
)

SET(TOOLKIT_CLIENTDB_NAMES ${TARGET_OBJECT_SUFFIX})
FIND_LIBRARY(TOOLKIT_CLIENTDB_LIBRARY
  NAMES ${TOOLKIT_CLIENTDB_NAMES}
  PATHS /usr/lib/toolkit /usr/local/lib/toolkit $ENV{HOME}/development/toolkit/common/build-c++
  PATH_SUFFIXES ${TARGET_OBJECT_SUFFIX}
)

IF (TOOLKIT_CLIENTDB_INCLUDE_DIR AND TOOLKIT_CLIENTDB_LIBRARY)
  SET(TOOLKIT_CLIENTDB_FOUND TRUE)
  SET( TOOLKIT_CLIENTDB_LIBRARIES ${TOOLKIT_CLIENTDB_LIBRARY} )
ELSE (TOOLKIT_CLIENTDB_INCLUDE_DIR AND TOOLKIT_CLIENTDB_LIBRARY)
  SET(TOOLKIT_CLIENTDB_FOUND FALSE)
  SET( TOOLKIT_CLIENTDB_LIBRARIES )
ENDIF (TOOLKIT_CLIENTDB_INCLUDE_DIR AND TOOLKIT_CLIENTDB_LIBRARY)

IF (TOOLKIT_CLIENTDB_FOUND)
  IF (NOT TOOLKIT_CLIENTDB_FIND_QUIETLY)
    MESSAGE(STATUS "Found ${TARGET_OBJECT_SUFFIX}: ${TOOLKIT_CLIENTDB_LIBRARY}")
  ENDIF (NOT TOOLKIT_CLIENTDB_FIND_QUIETLY)
ELSE (TOOLKIT_CLIENTDB_FOUND)
  IF (TOOLKIT_CLIENTDB_FIND_REQUIRED)
    MESSAGE(STATUS "Looked for ${TARGET_OBJECT_SUFFIX} libraries named ${TOOLKIT_CLIENTDB_NAMES}.")
    MESSAGE(FATAL_ERROR "Could NOT find toolkit-client library")
  ENDIF (TOOLKIT_CLIENTDB_FIND_REQUIRED)
ENDIF (TOOLKIT_CLIENTDB_FOUND)

MARK_AS_ADVANCED(
  TOOLKIT_CLIENTDB_LIBRARY
  TOOLKIT_CLIENTDB_INCLUDE_DIR
  )