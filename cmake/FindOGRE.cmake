# Find OGRE includes and library
#
# This module defines
#  OGRE_INCLUDE_DIRS
#  OGRE_LIBRARIES, the libraries to link against to use OGRE.
#  OGRE_LIBRARY_DIRS, the location of the libraries
#  OGRE_FOUND, If false, do not try to use OGRE
#
# Copyright © 2007-2008, Matt Williams
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

IF (OGRE_LIBRARIES AND OGRE_INCLUDE_DIRS)
	SET(OGRE_FIND_QUIETLY TRUE) # Already in cache, be silent
ENDIF (OGRE_LIBRARIES AND OGRE_INCLUDE_DIRS)

#Set the library and include search paths
#SET(OGRESDK $ENV{OGRE_HOME})
#STRING(REGEX REPLACE "[\\]" "/" OGRESDK "${OGRESDK}")
FILE(TO_CMAKE_PATH "$ENV{OGRE_HOME}" OGRESDK)
SET(OGRE_INCLUDE_SEARCH_DIRS #                 this <-
	${INCLUDE_SEARCH_DIRS} #TODO Cache this, not ^
	${CMAKE_LIBRARY_PATH}
	/usr/include/OGRE
	/usr/local/include/OGRE
	/opt/include/OGRE
	/opt/OGRE/include
	${OGRESDK}/include
	${OGRESDK}/OgreMain/include
	CACHE STRING ""
)

SET(OGRE_LIBRARY_SEARCH_DIRS
	${LIBRARY_SEARCH_DIRS}
	${CMAKE_LIBRARY_PATH}
	/usr/lib
	/usr/lib64
	/usr/local/lib
	/usr/local/lib64
	/opt/lib
	/opt/lib64
	/opt/OGRE/lib
	/opt/OGRE/lib64
	${OGRESDK}/lib
	${OGRESDK}/lib64
	CACHE STRING ""
)

# Allow to set Ogre plugin path manually
SET(OGRE_PLUGINDIR "" CACHE STRING "Ogre plugin directory")

#Search for the headers and libraries
IF (WIN32) #Windows
	MESSAGE(STATUS "Looking for OGRE")
	FIND_PATH(OGRE_INCLUDE_DIRS Ogre.h ${OGRE_INCLUDE_SEARCH_DIRS})
	FIND_LIBRARY(OGRE_LIBRARIES debug OgreMain_d optimized OgreMain PATHS ${OGRE_LIBRARY_SEARCH_DIRS})
ELSE (WIN32) #Unix/OSX
	FIND_PACKAGE(PkgConfig)
	IF(PKG_CONFIG_FOUND)
		PKG_SEARCH_MODULE(OGRE OGRE)
		IF(NOT PKGCONFIG_FAILED)
			_PKGCONFIG_INVOKE(OGRE "OGRE" PLUGINDIR "" --variable=plugindir)
			ADD_DEFINITIONS(-DOGRE_PLUGINDIR="${OGRE_PLUGINDIR}")
		ENDIF(NOT PKGCONFIG_FAILED)
		SET(OGRE_INCLUDE_DIRS ${OGRE_INCLUDE_DIRS})
		SET(OGRE_LIBRARY_DIRS ${OGRE_LIBDIR})
		SET(OGRE_LIBRARIES ${OGRE_LIBRARIES} CACHE STRING "")
	ENDIF(PKG_CONFIG_FOUND)
	IF(NOT OGRE_FOUND) #If PkgConfig couldn't find OGRE...
		IF (NOT OGRE_FIND_QUIETLY)
			MESSAGE(STATUS " Manually searching for OGRE")
		ENDIF (NOT OGRE_FIND_QUIETLY)
		FIND_PATH(OGRE_INCLUDE_DIRS Ogre.h ${OGRE_INCLUDE_SEARCH_DIRS})
		FIND_LIBRARY(OGRE_LIBRARIES OgreMain PATHS ${OGRE_LIBRARY_SEARCH_DIRS})
	ENDIF(NOT OGRE_FOUND)
ENDIF (WIN32)

#Do some preparation
SEPARATE_ARGUMENTS(OGRE_INCLUDE_DIRS)
SEPARATE_ARGUMENTS(OGRE_LIBRARIES)

SET(OGRE_INCLUDE_DIRS ${OGRE_INCLUDE_DIRS})
SET(OGRE_LIBRARIES ${OGRE_LIBRARIES})
SET(OGRE_LIBRARY_DIRS ${OGRE_LIBRARY_DIRS})

MARK_AS_ADVANCED(OGRE_INCLUDE_DIRS OGRE_LIBRARIES OGRE_LIBRARY_DIRS) #So they don't show in the default GUI

IF (OGRE_INCLUDE_DIRS AND OGRE_LIBRARIES)
	SET(OGRE_FOUND TRUE)
ENDIF (OGRE_INCLUDE_DIRS AND OGRE_LIBRARIES)

IF (OGRE_FOUND)
	IF (NOT OGRE_FIND_QUIETLY)
		MESSAGE(STATUS "  libraries : ${OGRE_LIBRARIES} from ${OGRE_LIBRARY_DIRS}")
		MESSAGE(STATUS "  includes  : ${OGRE_INCLUDE_DIRS}")
	ENDIF (NOT OGRE_FIND_QUIETLY)
ELSE (OGRE_FOUND)
	IF (OGRE_FIND_REQUIRED)
		MESSAGE(FATAL_ERROR "Could not find OGRE. Make sure you have the OGRE development headers installed. Otherwise, try setting LIBRARY_SEARCH_DIRS and INCLUDE_SEARCH_DIRS to the place OGRE was installed with -DLIBRARY_SEARCH_DIRS=<path/to/lib> -DINCLUDE_SEARCH_DIRS=<path/to/include>")
	ENDIF (OGRE_FIND_REQUIRED)
ENDIF (OGRE_FOUND)
