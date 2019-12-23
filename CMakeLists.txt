cmake_minimum_required(
	VERSION
    3.12.4
)

cmake_policy(
	SET
	CMP0043 OLD
)

project(
    SceneSample
)

set(
    CMAKE_AUTOMOC
    ON
)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set(
		CMAKE_INSTALL_PREFIX
        "${PROJECT_BINARY_DIR}/snapshot"
		CACHE
			PATH
			"Path to snapshot."
		FORCE
	)
endif()

# To fix x86 build with Angle (see https://bugreports.qt.io/browse/QTBUG-33534)
add_definitions(-DQT_OPENGL_ES_2)

include(
    ${PROJECT_SOURCE_DIR}/cmake/npm/NastyPackageManager.cmake
)

NPM_ADD_PACKAGE(
    NAME
        Qt
    VERSION
        5.12.5
    BUILD_NUMBER
        3
    TAG
        "sdk18362_vsbt19"
)

NPM_PREPARE_PACKAGES(
	DEFAULT_REPOSITORY_URLS
        "https://cnpm.rogii.com/windows/public"
)

set(
    SOURCES

    LogTrackSceneCameraManipulator.cpp
    QtQuickBased2DSceneCoordinatesMapper.cpp
    QtQuickBased2DSceneManipulatorTool.cpp
    Scene.cpp
    SceneArea.cpp
    SceneItem.cpp
    SceneCamera.cpp
    Base2DSceneCoordinatedMapper.cpp
    utils.cpp
    LineStrip.cpp
    FlatColorSceneMaterial.cpp
    SceneMaterial.cpp

    main.cpp
)

set(
    HEADERS

    I2DSceneManipulator.hpp
    I2DSceneCoordinatesMapper.hpp
    IChildMouseEventListener.hpp
    LogTrackSceneCameraManipulator.hpp
    QtQuickBased2DSceneCoordinatesMapper.hpp
    QtQuickBased2DSceneManipulatorTool.hpp
    Scene.hpp
    SceneArea.hpp
    SceneItem.hpp
    SceneCamera.hpp
    Base2DSceneCoordinatedMapper.hpp
    utils.hpp
    LineStrip.hpp
    FlatColorSceneMaterial.hpp
    SceneMaterial.hpp
)

qt5_add_resources(
    QRESOURCES
    resources.qrc
)

add_executable(
    ${PROJECT_NAME}
    WIN32
    ${HEADERS}
    ${SOURCES}
    ${QRESOURCES}
)

target_link_libraries(
    ${PROJECT_NAME}
    Qt5::Widgets
    Qt5::Quick
)

CNPM_INSTALL_EXPLICIT_ALL(
    TARGET_NAME
    ${PROJECT_NAME}
)

