cmake_minimum_required(VERSION 3.15)

project(AirportParkingClassifier)

set(CMAKE_CXX_STANDARD 17)

set(ONNXRUNTIME_DIR "C:/onnxruntime")
set(OPENCV_DIR "C:/opencv/build")

include_directories(
    include
    ${ONNXRUNTIME_DIR}/include
    ${OPENCV_DIR}/include
)

link_directories(
    ${ONNXRUNTIME_DIR}/lib
    ${OPENCV_DIR}/x64/vc16/lib
)

add_executable(
    airport_parking_classifier
    src/main.cpp
    src/OnnxEngine.cpp
    src/ImageLoader.cpp
    src/CsvWriter.cpp
    src/InferenceEngine.cpp
    src/ImageProcessor.cpp
    src/ResultVisualizer.cpp
    src/ConfigManager.cpp
    src/Logger.cpp
    src/OracleImageReader.cpp
    src/PricingEngine.cpp
)

target_link_libraries(
    airport_parking_classifier
    onnxruntime
    opencv_world4120
)