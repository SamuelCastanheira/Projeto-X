cmake_minimum_required(VERSION 4.1.1)

project(PROJETO-X LANGUAGES CXX)

# Adiciona flags para linkagem estática do runtime do GCC
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")

# Força o uso da biblioteca estática do GLUT
set(GLUT_USE_STATIC_LIBS TRUE)

find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(trabalho trabalho.cpp)

target_include_directories(trabalho PRIVATE src)

target_link_libraries(trabalho PRIVATE OpenGL::GL OpenGL::GLU GLUT::GLUT Boost::system)

# Comando para copiar as texturas
add_custom_command(TARGET trabalho POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/textura"
    "$<TARGET_FILE_DIR:trabalho>/textura"
    COMMENT "Copiando texturas para o diretório de compilação")