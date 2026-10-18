cmake_minimum_required(VERSION 3.28)

project(OCR LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 23)

include_directories(PUBLIC "include/shared")


add_library(ocr_lib STATIC 
"src/shared/FileUtil.cpp"
"src/shared/preprocessing/image.cpp"
"include/shared/preprocessing/dataset.ipp"
"include/shared/neural_network/neuralNetwork.ipp"
"include/shared/neural_network/layer.ipp"
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

# Test mains. Each file in the testing directory is a standalone program.
# Change the source in add_executable to change what is being tested
if(true)
    add_executable(test "src/testing/NeuralNetwork.cpp")
    target_include_directories(test PUBLIC "include/shared")
    target_link_libraries(test ocr_lib)
endif()