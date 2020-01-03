#SET(CMAKE_FIND_LIBRARY_SUFFIXES .a .so)
IF (OCTETOS_DB_MYSQL_INCLUDE_DIR)
  # Already in cache, be silent
  SET(OCTETOS_DB_MYSQL_FIND_QUIETLY TRUE)
ENDIF (OCTETOS_DB_MYSQL_INCLUDE_DIR)


FIND_PATH(OCTETOS_DB_MYSQL_INCLUDE_DIR db/clientdb-mysql.hh
        /usr/local/include/octetos
        /usr/include/octetos
)


FIND_LIBRARY(OCTETOS_DB_LIBRARY liboctetos-db.so
        NAMES ${OCTETOS_DB_NAMES}
        PATHS /lib /lib64 /lib32 /usr/local/lib/ /usr/lib/x86_64-linux-gnu/
        PATH_SUFFIXES octetos-db
)
FIND_LIBRARY(OCTETOS_DB_MYSQL_LIBRARY
        NAMES liboctetos-db-mysql.so
        PATHS /lib /lib64 /lib32 /usr/local/lib/ /usr/lib/x86_64-linux-gnu/
        PATH_SUFFIXES octetos-db-mysql
)


IF (OCTETOS_DB_MYSQL_INCLUDE_DIR)
  SET(OCTETOS_DB_MYSQL_FOUND TRUE)
  SET(OCTETOS_DB_MYSQL_LIBRARIES ${OCTETOS_DB_LIBRARY} ${OCTETOS_DB_MYSQL_LIBRARY} )
ELSE (OCTETOS_DB_MYSQL_INCLUDE_DIR)
  SET(OCTETOS_DB_MYSQL_FOUND FALSE)
  SET(OCTETOS_DB_MYSQL_LIBRARIES )
ENDIF (OCTETOS_DB_MYSQL_INCLUDE_DIR)

IF (OCTETOS_DB_MYSQL_FOUND)
  IF (NOT OCTETOS_DB_MYSQL_FIND_QUIETLY)
    MESSAGE(STATUS "Found DB MySQL de Octetos: ${OCTETOS_DB_MYSQL_LIBRARY}")
  ENDIF (NOT OCTETOS_DB_MYSQL_FIND_QUIETLY)
ELSE (OCTETOS_DB_MYSQL_FOUND)
  IF (OCTETOS_DB_MYSQL_FIND_REQUIRED)
    MESSAGE(STATUS "Looked for Toolkit octeos-db-mysql C++ libraries named ${OCTETOS_DB_MYSQL_NAMES}.")
    MESSAGE(FATAL_ERROR "Could NOT find octeos-db-mysql library")
  ENDIF (OCTETOS_DB_MYSQL_FIND_REQUIRED)
ENDIF (OCTETOS_DB_MYSQL_FOUND)

MARK_AS_ADVANCED(
  OCTETOS_DB_MYSQL_LIBRARY
  OCTETOS_DB_MYSQL_INCLUDE_DIR
  )
#SET(CMAKE_FIND_LIBRARY_SUFFIXES .so)