get_filename_component(CURRENT_DIR ${CMAKE_CURRENT_LIST_FILE} PATH)


include_directories("${CURRENT_DIR}/.." "${CURRENT_DIR}/RHI/.." "${CURRENT_DIR}/RHI/OpenGL/.." "${CURRENT_DIR}/RenderPipeline/.." "${CURRENT_DIR}/RenderPipeline/base/.." "${CURRENT_DIR}/Base/..")


file(GLOB Base_SOURCES
        "${CURRENT_DIR}/Base/*.cpp"
        "${CURRENT_DIR}/Base/*.h"
        )

file(GLOB RenderPipeline_SOURCES
        "${CURRENT_DIR}/RenderPipeline/*.cpp"
        "${CURRENT_DIR}/RenderPipeline/*.h"
        "${CURRENT_DIR}/RenderPipeline/base/*.cpp"
        "${CURRENT_DIR}/RenderPipeline/base/*.h"
        )

FilterFolder("${RenderPipeline_SOURCES}")

file(GLOB RHI_SOURCES
        "${CURRENT_DIR}/RHI/*.cpp"
        "${CURRENT_DIR}/RHI/*.h"
        "${CURRENT_DIR}/RHI/OpenGL/*.cpp"
        "${CURRENT_DIR}/RHI/OpenGL/*.h"
)
FilterFolder("${RHI_SOURCES}")

list(APPEND SOURCES ${RenderPipeline_SOURCES} ${Base_SOURCES} ${RHI_SOURCES})

# 生成链接库
add_library(engine ${SOURCES})

find_package(glad)
include_directories("${glad_INCLUDE_DIRS}")

find_package(stb_image)
include_directories("${stb_image_INCLUDE_DIRS}")

find_package(glm)
include_directories("${glm_INCLUDE_DIRS}")

target_link_libraries(engine ${glad_LIBRARIES})
