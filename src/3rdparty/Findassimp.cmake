get_filename_component(THIRDPARTY_DIR ${CMAKE_CURRENT_LIST_FILE} PATH)

set(assimp_INCLUDE_DIRS "${THIRDPARTY_DIR}/assimp" )
message("findassimp ${assimp_INCLUDE_DIRS}" )

