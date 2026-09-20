cmake_minimum_required(VERSION 3.28)

project(OCR LANGUAGES CXX)


include_directories(PUBLIC "include/shared")
include_directories(PUBLIC "include/shared.")

add_library(ocr_lib STATIC 
"src/shared/test.cpp" 
"src/shared/stb_image.cpp"
"src/shared/data_structures/abstract_matrix.cpp"
"src/shared/data_structures/matrix.cpp"
"src/shared/data_structures/vector.cpp"
"src/shared/preprocessing/image.cpp"
"src/shared/preprocessing/dataset.cpp"
"src/shared/preprocessing/batch.cpp"
)


# Extract
add_executable(extract "src/extract/main.cpp") # No includes for Extract specifically: it should be pretty simple, I'd think.
target_link_libraries(extract ocr_lib)


# Train
add_executable(train "src/train/main.cpp")
target_include_directories(train PUBLIC "include/train")
target_link_libraries(train ocr_lib)

# Classify
add_executable(classify "src/classify/main.cpp")
target_include_directories(classify PUBLIC "include/classify")
target_link_libraries(classify ocr_lib)
