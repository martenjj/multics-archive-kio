
set(kiomultics_SRCS
    kiomultics.cpp
)

ecm_qt_declare_logging_category(kiomultics_SRCS
    HEADER loggingcategory.h
    IDENTIFIER KIOMulticsLog
    CATEGORY_NAME kiomultics
    DEFAULT_SEVERITY Debug
)

add_library(KIOMultics ${kiomultics_SRCS})
generate_export_header(KIOMultics BASE_NAME KIOMultics)

# target_include_directories(KF5Archive
    # INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF5}/KArchive>"
# )

target_link_libraries(KIOMultics
    PUBLIC
        Qt5::Core
    PRIVATE
        KF5::I18n
        KF5::Archive
)


set_target_properties(KIOMultics PROPERTIES SOVERSION ${SOVERSION})

ecm_generate_headers(KIOMultics_HEADERS
    HEADER_NAMES
    KIOMultics
    REQUIRED_HEADERS KIOMultics_HEADERS
)

install(TARGETS KIOMultics
        # EXPORT KF5ArchiveTargets
        ${KF5_INSTALL_TARGETS_DEFAULT_ARGS})

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/kiomultics_export.h ${KIOMultics_HEADERS}
  DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/KIOMultics
  COMPONENT Devel)

# include(ECMGeneratePriFile)
# ecm_generate_pri_file(BASE_NAME KArchive LIB_NAME KF5Archive DEPS "core" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF5}/KArchive)
# install(FILES ${PRI_FILENAME}
        # DESTINATION ${ECM_MKSPECS_INSTALL_DIR})

