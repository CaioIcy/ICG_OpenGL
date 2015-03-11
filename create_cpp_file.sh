#!/bin/bash
set -o posix

function attention_echo {
	echo -e "\n******************************************"
	echo -e "*\t$1 *"
	echo -e "******************************************\n"
}

# The possible arguments to pass to this script
ARG_FOLDER_AUDIO="audio"
ARG_FOLDER_CORE="core"
ARG_FOLDER_ENGINE="engine"
ARG_FOLDER_GRAPHICS="graphics"
ARG_FOLDER_INPUT="input"
ARG_FOLDER_UTIL="util"

MAIN_PROJECT_NAMESPACE="ogle"

# Some directories
DIR_PROJECT_ROOT=$(dirname "$(readlink -f $0)")
DIR_SRC=${DIR_PROJECT_ROOT}/src
DIR_SRC_AUDIO=${DIR_SRC}/${ARG_FOLDER_AUDIO}
DIR_SRC_CORE=${DIR_SRC}/${ARG_FOLDER_CORE}
DIR_SRC_ENGINE=${DIR_SRC}/${ARG_FOLDER_ENGINE}
DIR_SRC_GRAPHICS=${DIR_SRC}/${ARG_FOLDER_GRAPHICS}
DIR_SRC_INPUT=${DIR_SRC}/${ARG_FOLDER_INPUT}
DIR_SRC_UTIL=${DIR_SRC}/${ARG_FOLDER_UTIL}

HEADER_FILE_TEXT=

function usage {
	echo "The correct usage of this script:"
	echo -e "\t./create_cpp_file.sh <src folder> <filename>\n"
	exit 2
}

function check_valid_folder {
	if [ $1 == "${ARG_FOLDER_AUDIO}" ] || [ $1 == "${ARG_FOLDER_CORE}" ] || \
		[ $1 == "${ARG_FOLDER_ENGINE}" ] || [ $1 == "${ARG_FOLDER_GRAPHICS}" ] || \
		[ $1 == "${ARG_FOLDER_INPUT}" ] || [ $1 == "${ARG_FOLDER_UTIL}" ]
	then
		return 0
	else
		attention_echo "'$1' is an invalid source folder."
		return 1
	fi
}

function create_files {
	touch ${DIR_SRC}/$1/$2.h
	printf "\
#pragma once\n\
\n\
namespace ${MAIN_PROJECT_NAMESPACE} {\n\
\n\
class $2 {\n\
\n\
\tpublic:\n\
\t\t$2();\n\
};\n\
\n\
} // namespace ${MAIN_PROJECT_NAMESPACE}\n" > ${DIR_SRC}/$1/$2.h

	touch ${DIR_SRC}/$1/$2.cpp
	printf "\
#include \"$1/$2.h\"\n\
\n\
namespace ${MAIN_PROJECT_NAMESPACE} {\n\
\n\
$2::$2() {\n\
}\n\
\n\
} // namespace ${MAIN_PROJECT_NAMESPACE}\n" > ${DIR_SRC}/$1/$2.cpp

}

#########################################
################ "Main" #################
#########################################

attention_echo "Beggining create C++ file script"

if [ ! -z $1 ] && [ ! -z $2 ]
then

	if check_valid_folder $1
	then
		create_files $1 $2
	else
		usage
	fi

# If the first argument is empty
else
	usage
fi
