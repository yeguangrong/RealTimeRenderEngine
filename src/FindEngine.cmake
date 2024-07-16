get_filename_component(CURRENT_DIR ${CMAKE_CURRENT_LIST_FILE} PATH)

set(engine_INCLUDE_DIRS "${CURRENT_DIR}" "${CURRENT_DIR}/Engine/RenderPipeline")
set(engine_LIBRARIES engine)