#
#  Copyright 2010 CNRS
#  Author: Florent Lamiraux
#

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.3)

find_package(catkin REQUIRED COMPONENTS sot_cmake dynamic-graph-python)

INCLUDE(${SOT_CMAKE_DIR}/base.cmake)
INCLUDE(${SOT_CMAKE_DIR}/boost.cmake)
INCLUDE(${SOT_CMAKE_DIR}/lapack.cmake)
INCLUDE(${SOT_CMAKE_DIR}/cpack.cmake)

SET(PROJECT_NAME dynamic-graph-tutorial)
project(${PROJECT_NAME})

include_directories(${catkin_INCLUDE_DIRS})

catkin_package()

SET(PROJECT_VERSION 1.0)
SET(PROJECT_DESCRIPTION "Tutorial for dynamic-graph")
SET(PROJECT_URL "http://github.com/jrl-umi3218/dynamic-graph-tutorial")

SET(${PROJECT_NAME}_HEADERS
    include/dynamic-graph/tutorial/inverted-pendulum.hh
    include/dynamic-graph/tutorial/feedback-controller.hh
)
#
# Look for dependencies
#

SETUP_PROJECT()

#

ADD_SUBDIRECTORY(src)
#ADD_SUBDIRECTORY(doc)

SETUP_PROJECT_FINALIZE()
