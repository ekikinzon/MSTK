
include_directories(${PROJECT_SOURCE_DIR}/include)


add_executable(chkmesh src/chkmesh.c src/geom.c)
target_link_libraries(chkmesh 
                      ${MSTKLIB} 
                      ${MSTK_TPL_LIBRARIES} 
                      m)

# Would be nice to specify it relative to the path of this CMakeLists.txt file

if (INSTALL_DIR) 
  if (INSTALL_PREFIX_ARCHOS)
    install(TARGETS chkmesh DESTINATION ${INSTALL_DIR}/bin/${ARCHOS})
  else ()
    install(TARGETS chkmesh DESTINATION ${INSTALL_DIR}/bin)
  endif ()
else ()
  if (INSTALL_PREFIX_ARCHOS)
    install(TARGETS chkmesh DESTINATION ${PROJECT_SOURCE_DIR}/bin/${ARCHOS})
  else ()
    install(TARGETS chkmesh DESTINATION ${PROJECT_SOURCE_DIR}/bin)
  endif ()
endif ()


