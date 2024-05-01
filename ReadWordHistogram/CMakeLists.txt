# CMakeList.txt: проект CMake для ReadWordHistogram; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_PREFIX_PATH "C:/Qt/6.6.0/msvc2019_64")
set(QT_BIN_DIR "C:/Qt/6.6.0/msvc2019_64/bin")
set(QT_PLUGINS_DIR "C:/Qt/6.6.0/msvc2019_64/plugins")
find_package(Qt6 COMPONENTS Core Gui Qml Widgets Quick REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



list(APPEND CMAKE_MODULE_PATH "C:/Qt/6.6.0/msvc2019_64/lib/cmake/Qt6Core")
# Укажите путь к директории плагинов Qt
# Установка путей для ресурсов
set(RESOURCES_PATH "C:/Users/dark_/Desktop/TwoGis/ReadWordHistogram/ReadWordHistogram/resources.qrc")

# Добавление исходных файлов
set(SOURCES
    controlbuttons.cpp
    itemhistogram.cpp
    ReadWordHistogram.cpp
    texthandler.cpp
)

# Добавление заголовочных файлов
set(HEADERS
    IHistogram.h
    ITextHandler.h
    controlbuttons.h
    itemhistogram.h
    texthandler.h
)
qt_add_resources(RESOURCES ${RESOURCES_PATH})
#qt_standard_project_setup()
# Создание исполняемого файла
add_executable(ReadWordHistogram ${SOURCES} ${HEADERS})
# Добавьте источник в исполняемый файл этого проекта.
#add_executable (ReadWordHistogram "ReadWordHistogram.cpp" "ReadWordHistogram.h")

# Связывание с библиотеками Qt
target_link_libraries(ReadWordHistogram PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Qml Qt6::Quick)


# Добавление ресурсов

# Установка путей для ресурсов
target_sources(ReadWordHistogram PRIVATE ${RESOURCES})
set_target_properties(ReadWordHistogram PROPERTIES
    QML_IMPORT_NAME "io.qt.examples.backend"
    QML_IMPORT_MAJOR_VERSION 1
)


qt_add_qml_module(ReadWordHistogram
    URI resources
    VERSION 1.0
    QML_FILES main.qml)




if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ReadWordHistogram PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
