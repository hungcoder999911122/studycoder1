cmake_minimum_required(VERSION 3.10)
project(GITHUB_PROJECT_2)

set(CMAKE_CXX_STANDARD 17)

# CHỈ lấy các file .cpp ở thư mục ngoài, KHÔNG chui vào thư mục con (như build)
file(GLOB SOURCES "*.cpp")

# Nếu bạn để code trong thư mục src/ thì dùng dòng này:
# file(GLOB SOURCES "src/*.cpp")

add_executable(Task_6 ${SOURCES})