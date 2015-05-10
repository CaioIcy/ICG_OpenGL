message("\n*** src/ subdir")

###################################################################
message(AUTHOR_WARNING "Getting source files by using glob")
file(GLOB_RECURSE MyCppSources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

# Create a list with all cpp sources except for main, so the library doesn't contain it
set(MySourcesNoMain ${MyCppSources})
list(REMOVE_ITEM MySourcesNoMain main.cpp)

set(ExecTarget ${MyProjectName}_exec)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW3 REQUIRED glfw3)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
# find_package(gflags REQUIRED)

###################################################################
# Adding warning and standard flags here so we don't get an insane amount of warnings from
# externals, just from our project
if(MY_SHARED_LIB_ENABLED)
	add_library(${MyProjectLib} SHARED ${MySourcesNoMain})
else()
	add_library(${MyProjectLib} STATIC ${MySourcesNoMain})
endif()
set_target_properties(${MyProjectLib} PROPERTIES COMPILE_FLAGS "${FLAGS_MY_PROJECT}")

###################################################################
# Adding warning and standard flags here so we don't get an insane amount of warnings from
# externals, just from our project
add_executable(${ExecTarget} main.cpp)
set_target_properties(${ExecTarget} PROPERTIES COMPILE_FLAGS "${FLAGS_MY_PROJECT}")
target_link_libraries(${ExecTarget}
	${MyProjectLib}
	${GLFW3_STATIC_LIBRARIES}
	${GLEW_LIBRARIES}
	${SDL2_LIBRARY}
	${SDL2_IMAGE_LIBRARY}
	# gflags
)

include_directories(
	${PROJECT_SOURCE_DIR}/src
	${GLFW3_INCLUDE_DIR}
	${GLEW_INCLUDE_DIRS}
	${GLM_INCLUDE_DIRS}
	${SDL2_IMAGE_INCLUDE_DIR}
	# ${gflags_include_dir}
)

# If built with enabled timed run flag (from .travis.yml)
if(MY_TIMED_RUN_ENABLED)
	add_definitions(-DICYTIMEDRUN)
endif()

# Files that are packed with CPack
install(TARGETS ${ExecTarget}
	RUNTIME DESTINATION bin
	COMPONENT executables
)

if(MY_SHARED_LIB_ENABLED)
	install(TARGETS ${MyProjectLib}
		LIBRARY DESTINATION bin
		COMPONENT executables
	)
endif()

install(DIRECTORY ${PROJECT_SOURCE_DIR}/assets
	DESTINATION bin
	COMPONENT assets
)

# Licensing and stuff like that
install(FILES
	${ReadmeFile}
	${LicenseFile}
	DESTINATION .
)
