#########################################################################
#  Project:		KDE - Multics Archive Reader			#
#  Edit:		16-Mar-17					#
#########################################################################
#									#
#  Copyright (c) 2017 Jonathan Marten <jjm@keelhaul.me.uk>		#
#  Home and download page:  http:#github.com/martenjj/kiomultics	#
#									#
#  This program is free software; you can redistribute it and/or	#
#  modify it under the terms of the GNU General Public License as	#
#  published by the Free Software Foundation; either version 2 of	#
#  the License, or (at your option) any later version.			#
#									#
#  It is distributed in the hope that it will be useful, but		#
#  WITHOUT ANY WARRANTY; without even the implied warranty of		#
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the	#
#  GNU General Public License for more details.				#
#									#
#  You should have received a copy of the GNU General Public		#
#  License along with this program; see the file COPYING for further	#
#  details.  If not, see <http://www.gnu.org/licenses>.			#
#									#
#########################################################################

cmake_minimum_required(VERSION 3.0)
set(VERSION "0.1.0")
project(kio-multics VERSION ${VERSION})

#########################################################################
#									#
#  ECM paths and definitions						#
#									#
#########################################################################

set(QT_MIN_VERSION "5.6.0")
set(KF5_MIN_VERSION "5.31.0")
set(ECM_MIN_VERSION "5.31.0")

find_package(ECM ${ECM_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

include(ECMSetupVersion)
include(ECMGenerateHeaders)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(FeatureSummary)

#########################################################################
#									#
#  Subdirectories							#
#									#
#########################################################################

add_subdirectory(src)

#########################################################################
#									#
#  Information at end of cmake run					#
#									#
#########################################################################

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
