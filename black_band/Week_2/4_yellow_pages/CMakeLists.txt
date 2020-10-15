cmake_minimum_required(VERSION 3.17)
project(4_yellow_pages)

set(CMAKE_CXX_STANDARD 20)
find_package(Protobuf REQUIRED) # Команда находит пути к компилятору protoc и библиотеке libprotobuf
include_directories(${Protobuf_INCLUDE_DIRS}) # Добавляем в include path пути к библиотеке protobuf
include_directories(${CMAKE_CURRENT_BINARY_DIR}) # В ${CMAKE_CURRENT_BINARY_DIR} будут файлы, сгенерированные компилятором protoс, путь к ним надо добавить в include path

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS protos/address.proto protos/company.proto protos/name.proto protos/phone.proto protos/provider.proto protos/signal.proto protos/url.proto protos/working_time.proto) # Здесь надо перечислить все ваши .proto-файлы
add_executable(4_yellow_pages ${PROTO_SRCS} ${PROTO_HDRS} merge.cpp test.cpp) # Здесь надо перечислить все ваши .cpp-файлы, в том числе и сгенерированные protoc'ом
target_link_libraries(4_yellow_pages ${Protobuf_LIBRARIES}) # компонуем наш исполняемый файл с библиотекой libprotobuf
