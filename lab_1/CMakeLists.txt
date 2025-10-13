# CMakeList.txt: проект CMake для lab_1_v2; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (lab_1_v2 "main.cpp"   "application.cpp" "application.h" "array.h" "list.h" "station.cpp" "station.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET lab_1_v2 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
