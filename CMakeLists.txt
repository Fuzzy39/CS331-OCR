cmake_minimum_required(VERSION 3.28)

project(OCR LANGUAGES CXX)


include_directories(PUBLIC "include/shared")

add_library(ocr_lib STATIC "src/shared/test.cpp" "src/shared/stb_image.cpp")

add_executable(train "src/train/main.cpp")
target_include_directories(train PUBLIC "include/train")
target_link_libraries(train ocr_lib)

add_executable(classify "src/classify/main.cpp")
target_include_directories(classify PUBLIC "include/classify")
target_link_libraries(classify ocr_lib)
