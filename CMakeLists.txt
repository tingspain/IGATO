PROJECT(IGATO)

SET (PACKAGE "IGATO")
SET (VERSION "0.0.1")

SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/../../cmake_modules)

IF(NOT CMAKE_BUILD_TYPE)
	SET(CMAKE_BUILD_TYPE Release CACHE STRING
			"Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
	FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)



# Provides build options to CMake
# Build Option: when active builds MIDACO
#OPTION(BUILD_MIDACO)

# Build Option: when active builds SNOPT
#OPTION(BUILD_SNOPT)



# astro kit lib source files.
SET(ASTRO_KIT_SRC_LIST
	${CMAKE_CURRENT_SOURCE_DIR}/proj/astro_kit/src/Orbit.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/proj/astro_kit/src/Transformation.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/proj/astro_kit/src/KeplersEquations.cpp
	)

#Build Static Library
ADD_LIBRARY(astro_kit STATIC ${ASTRO_KIT_SRC_LIST}

