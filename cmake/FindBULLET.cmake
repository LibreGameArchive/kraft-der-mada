# Find BULLET
#
# This module defines
# BULLET_FOUND       - BULLET was found
# BULLET_INCLUDE_DIR - Directory containing BULLET header files
# BULLET_LIBRARIES     - Library name of BULLET library
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

# On a new cmake run, we do not need to be verbose
IF(BULLET_INCLUDE_DIR AND BULLET_LIBRARY)
	SET(BULLET_FOUND_QUIETLY TRUE)
ENDIF(BULLET_INCLUDE_DIR AND BULLET_LIBRARY)

IF(WIN32)

ELSE(WIN32)
	IF(NOT BULLET_FOUND)
		SET(BULLET_INCLUDE_SEARCH_DIRS
		    /usr/include
		    /usr/local/include
		    /opt/include
		    /opt/BULLET/include)
		SET(BULLET_LIBRARY_SEARCH_DIRS
		    /usr/lib
		    /usr/lib64
		    /usr/local/lib
		    /usr/local/lib64
		    /opt/BULLET/lib
		    /opt/BULLET/lib64)
		SET(BULLET_INC_DIR_SUFFIXES PATH_SUFFIXES BULLET)
		FIND_PATH(BULLET_INCLUDE_DIR btBulletDynamicsCommon.h
		          PATHS ${BULLET_INCLUDE_SEARCH_DIRS}
		          PATH_SUFFIXES ${BULLET_INC_DIR_SUFFIXES})
		SET(BULLET_LIBRARIES BulletDynamics  BulletCollision LinearMath)
		FIND_PATH(BULLET_LIBRARY_DIRS libBulletCollision.a
		             PATHS ${BULLET_LIBRARY_SEARCH_DIRS}
		             PATH_SUFFIXES ${BULLET_LIB_DIR_SUFFIXES}})
	ENDIF(NOT BULLET_FOUND)
ENDIF(WIN32)

SET(BULLET_INCLUDE_DIR ${BULLET_INCLUDE_DIR} CACHE STRING "Directory containing BULLET header files")
SET(BULLET_LIBRARIES ${BULLET_LIBRARIES} CACHE STRING "Library name of BULLET library")

IF(BULLET_INCLUDE_DIR AND BULLET_LIBRARY_DIRS)
	SET(BULLET_FOUND TRUE)
ENDIF(BULLET_INCLUDE_DIR AND BULLET_LIBRARY_DIRS)

IF(BULLET_FOUND)
	IF(NOT BULLET_FIND_QUIETLY)
		MESSAGE(STATUS "  libraries: ${BULLET_LIBRARIES} from ${BULLET_LIBRARY_DIRS}")
		MESSAGE(STATUS "  includes: ${BULLET_INCLUDE_DIR}")
	ENDIF(NOT BULLET_FIND_QUIETLY)
ELSE(BULLET_FOUND)
	IF(BULLET_FIND_REQUIRED)
		IF(NOT BULLET_LIBRARY_DIRS)
			MESSAGE(SEND_ERROR, "BULLET library could not be found.")
		ENDIF(NOT BULLET_LIBRARY)
		IF(NOT BULLET_INCLUDE_DIR)
			MESSAGE(SEND_ERROR "BULLET include files could not be found.")
		ENDIF(NOT BULLET_INCLUDE_DIR)
	ENDIF(BULLET_FIND_REQUIRED)
ENDIF(BULLET_FOUND)
