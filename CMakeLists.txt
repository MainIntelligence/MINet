
cmake_minimum_required(VERSION 3.5)

project(MINet)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS NO)

SET(exe)
SET(SOURCE_EXE)


add_subdirectory(Client)



include_directories(${INCLUDE_DIRS})


include(GNUInstallDirs)

#add_library(${PROJECT_NAME} ${SOURCE_CPPS})
#install(TARGETS ${PROJECT_NAME}
#	DESTINATION ${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}
#)

#install all the needed include directories
list(LENGTH INCLUDE_DIRS TOTAL_INCLUDES)
MATH(EXPR TOTAL_INCLUDES "${TOTAL_INCLUDES}-1")
foreach(i RANGE ${TOTAL_INCLUDES})
	list(GET INCLUDE_DIRS ${i} dir)
	install(DIRECTORY ${dir}/ 
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
		FILES_MATCHING PATTERN "*.h"
	)
endforeach()


message("SOURCE_EXE=${SOURCE_EXE}")

#build and install every executable
list(LENGTH SOURCE_EXE TOTAL_EXE)
MATH(EXPR TOTAL_EXE "${TOTAL_EXE}-1")
foreach(i RANGE ${TOTAL_EXE})
	list(GET SOURCE_EXE ${i} exe)
	list(GET EXE_NAMES ${i} exe_name)
	message("exe= ${exe}")
	add_executable(${exe_name} ${exe})
	#set_target_properties(${exe} PROPERTIES OUTPUT_NAME ${exe})
	#target_link_libraries(${exe} ${PROJECT_NAME})
	
	install(TARGETS ${exe_name}
		DESTINATION ${CMAKE_INSTALL_BINDIR}
	)
endforeach()



#add_executable(${PROJECT_NAME} ${SOURCE_EXE})
#set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

