get_filename_component(THIRDPARTY_DIR ${CMAKE_CURRENT_LIST_FILE} PATH)

set(assimp_INCLUDE_DIRS "${THIRDPARTY_DIR}/assimp" "${THIRDPARTY_DIR}/assimp/include" )
set(assimp_LIBRARIES "${THIRDPARTY_DIR}/glfw/lib/assimp.lib")
message("findassimp ${assimp_INCLUDE_DIRS}" )

