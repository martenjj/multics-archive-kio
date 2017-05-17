#########################################################################
#									#
#  Project:  KDE - Multics Archive Reader				#
#									#
#  Copyright (c) 2017 Jonathan Marten <jjm@keelhaul.me.uk>		#
#  Home & download:  http://github.com/martenjj/multics-archive-kio	#
#									#
#  This program is free software; you can redistribute it and/or	#
#  modify it under the terms of the GNU General Public License as	#
#  published by the Free Software Foundation; either version 3 of	#
#  the License, or (at your option) any later version.			#
#									#
#  It is distributed in the hope that it will be useful, but		#
#  WITHOUT ANY WARRANTY; without even the implied warranty of		#
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the	#
#  GNU General Public License for more details.				#
#									#
#  You should have received a copy of the GNU General Public		#
#  License along with this program; see the file LICENSE for further	#
#  details.  If not, see <http://www.gnu.org/licenses>.			#
#									#
#########################################################################

project(kio-multics)

find_package(Qt5 ${QT_MIN_VERSION} REQUIRED NO_MODULE COMPONENTS Core Widgets)
find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS I18n KIO Archive)

find_package(KioArchive REQUIRED NO_POLICY_SCOPE)
set_package_properties("KioArchive" PROPERTIES DESCRIPTION "Archive protocol base class library" TYPE REQUIRED PURPOSE "Required to build the archiver")

add_definitions(-DTRANSLATION_DOMAIN=\"kio_multics\")

add_library(archive_mxarc MODULE kio_archive_mxarc.cpp kmulticsarchive.cpp)
generate_export_header(archive_mxarc BASE_NAME kmulticsarchive EXPORT_FILE_NAME kmulticsarchive_export.h)
target_link_libraries(archive_mxarc Qt5::Core KF5::I18n KF5::KIOCore KF5::Archive KioArchive)
set_target_properties(archive_mxarc PROPERTIES OUTPUT_NAME "mxarc")

install(TARGETS archive_mxarc DESTINATION ${PLUGIN_INSTALL_DIR}/kf5/kio)
install(FILES mxarc.protocol DESTINATION ${SERVICES_INSTALL_DIR})
