
cmake_minimum_required(VERSION 3.0)

set(VERSION "0.1.0")
project(KIOMultics VERSION ${VERSION})
set(SOVERSION "1")

set(QT_MIN_VERSION "5.6.0")
set(KF5_MIN_VERSION "5.31.0")
set(ECM_MIN_VERSION "5.31.0")

include(FeatureSummary)

find_package(ECM ${ECM_MIN_VERSION} NO_MODULE REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

find_package(Qt5 ${QT_MIN_VERSION} REQUIRED NO_MODULE COMPONENTS Core)
find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS I18n Archive)

include(ECMSetupVersion)
include(ECMGenerateHeaders)
include(ECMQtDeclareLoggingCategory)
include(KDEInstallDirs)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(KDECMakeSettings)
include(GenerateExportHeader)

add_subdirectory(src)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
