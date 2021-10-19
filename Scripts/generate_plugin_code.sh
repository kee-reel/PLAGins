#!/bin/bash

read_option_num() {
	VAR_NAME=$1
	PROMPT=$2
	MIN=$3
	MAX=$4
	DEFAULT=$5
	if [[ -z "$DEFAULT" ]]; then
		PROMPT_TEMP="$PROMPT: "
	else
		PROMPT_TEMP="$PROMPT (press Enter to use default '$DEFAULT'): "
	fi
	
	read -p "$PROMPT_TEMP" REPLY
	if [[ -z "$REPLY" ]]; then
		if [[ -n "$DEFAULT" ]]; then
			REPLY=$DEFAULT
		else
			echo 'This question is mandatory'
			read_option_num "$VAR_NAME" "$PROMPT" $DEFAULT
			exit
		fi
	fi
	if [[ $REPLY -lt $MIN ]] || [[ $REPLY -gt $MAX ]]; then
		echo "Number not in range [$MIN, $MAX]"
		read_option_num "$VAR_NAME" "$PROMPT" $MIN $MAX $DEFAULT
	else
		eval "$VAR_NAME"=$REPLY
	fi
}
read_option() {
	VAR_NAME=$1
	PROMPT=$2
	DEFAULT=$3
	if [[ -z "$DEFAULT" ]]; then
		PROMPT_TEMP="$PROMPT: "
	else
		PROMPT_TEMP="$PROMPT (press Enter to use default '$DEFAULT'): "
	fi
	
	read -p "$PROMPT_TEMP" REPLY
	if [[ -z "$REPLY" ]]; then
		if [[ -n "$DEFAULT" ]]; then
			REPLY=$DEFAULT
		else
			echo 'This question is mandatory'
			read_option "$VAR_NAME" "$PROMPT" $DEFAULT
			exit
		fi
	fi
	eval "$VAR_NAME"="$REPLY"
}

read_option_yn() {
	VAR_NAME=$1
	PROMPT=$2
	DEFAULT=$3
	if [[ -z "$DEFAULT" ]]; then
		PROMPT_TEMP="$PROMPT (y/n)"
	else
		PROMPT_TEMP="$PROMPT (y/n) (press Enter to use default '$DEFAULT'): "
	fi
	read -p "$PROMPT_TEMP" REPLY
	if [[ -z "$REPLY" ]]; then
		if [[ -n "$DEFAULT" ]]; then
			REPLY=$DEFAULT
		else
			echo 'This question is mandatory'
			read_option_yn "$VAR_NAME" "$PROMPT" $DEFAULT
		fi
	fi
	case "$REPLY" in
		[yY][eE][sS]|[yY]) 
			eval "$VAR_NAME"=true
			;;
		[nN][oO]|[nN]) 
			eval "$VAR_NAME"=false
			;;
		*)
			echo 'Provided incorrect answer: expected "y" or "n"'
			read_option_yn "$VAR_NAME" "$PROMPT" $DEFAULT
	esac
}

IS_UI=false
HAS_INTERFACE=false

read_option NAME 'Specify name of your plugin in CamelCase'

if [[ -z "$(echo $NAME | grep -E '^[A-Z]')" ]]; then
	echo 'Plugin name must be in CamelCase!'
	exit
fi

if [[ -e "./Plugins/$NAME" ]]; then
	echo 'Plugin with same name already exists in ./Plugins!'
	exit
fi

read_option_yn IS_UI "Your plugin is graphical user interface for other plugin?" N

if ! $IS_UI; then
	read_option_yn HAS_INTERFACE "Are you planning to provide some of your plugin's functionality to other plugins?"
	if $HAS_INTERFACE ; then
		read_option I_NAME "Specify name of your plugin's interface" "I$NAME"
		I_FILENAME=$(echo "${I_NAME}.h" | sed -E 's/^I/i/' | 
			sed -E 's/([A-Z][a-z])/_\1/g' |
			sed -E 's/([a-z])([A-Z])/\1_\2/g' |
			tr '[:upper:]' '[:lower:]')
		read_option I_FILENAME "Specify filename of your plugin's interface " $I_FILENAME
		I_PATH="../../Interfaces/$I_FILENAME"
		if [[ -e $I_PATH ]]; then
			echo 'Interface with same name already exists in ./Plugins!'
			exit
		fi
		HDR_FILENAME=$(echo "$I_FILENAME" | sed -E 's/^i_(.+)/\1/')
		SRC_FILENAME=$(echo "$I_FILENAME" | sed -E 's/^i_(.+).h/\1.cpp/')
	fi
else
	read_option_num UI_TYPE "Your plugin will use:
1 - QML(recommended)
2 - QWidjets
Type option number" 1 2 1
	if [[ $UI_TYPE == '1' ]]; then
		REF_FILENAMES=($(ls -1 ./Interfaces | sort))
		echo "Your plugin is graphical user interface of other plugin. Please, choose name of file that contains interface of that plugin:"
		for ((i = 0; i < ${#REF_FILENAMES[@]}; i++)); do
			echo "$i: ${REF_FILENAMES[i]}"
		done
		read_option_num INDEX 'File index' 0 $((${#REF_FILENAMES[@]}-1))
		REF_FILENAME=${REF_FILENAMES[INDEX]}
		REF=$(grep -oE 'INTERFACE(.+),' Interfaces/$REF_FILENAME | sed -E 's/INTERFACE\((.+)\,/\1/')
		REF_FILENAME="../../Interfaces/$REF_FILENAME"
	fi
fi

cp -r ./Scripts/PluginTemplate ./Plugins/$NAME
cd ./Plugins/$NAME
DESC='Author of this plugin have nothing to say'

for f in $(ls | grep -E '\.(txt|cpp|h|qml|json)$'); do
	if $IS_UI; then
		sed -i -E "s/@UI@//g" $f
		if [[ $UI_TYPE == '1' ]]; then
			sed -i -E "s/@QML@//g" $f
			sed -i -E "/@WID@/d" $f
		else
			sed -i -E "s/@WID@//g" $f
			sed -i -E "/@QML@/d" $f
		fi
	else
		sed -i -E "/@(WID|QML|UI)/d" $f
	fi
	if $HAS_INTERFACE; then
		sed -i -E "s/@INT@//g" $f
	else
		sed -i -E "/@INT@/d" $f
	fi
	sed -i -E "s|%.CN.|$NAME|g" $f
	sed -i -E "s|%.Description.|$DESC|g" $f
	sed -i -E "s|%.HdrFileName.|$HDR_FILENAME|g" $f
	sed -i -E "s|%.SrcFileName.|$SRC_FILENAME|g" $f
	sed -i -E "s|%.InterfaceName.|$I_NAME|g" $f
	sed -i -E "s|%.IPath.|$I_PATH|g" $f
	sed -i -E "s|%.REF_FILENAME.|$REF_FILENAME|g" $f
	sed -i -E "s|%.REF.|$REF|g" $f
done


if $IS_UI; then
	if [[ $UI_TYPE == '1' ]]; then
		rm form.ui
	else
		rm form.qml res.qrc
	fi
else
	rm form.qml form.ui res.qrc
fi
echo "$HAS_INTERFACE $IS_UI"
if $HAS_INTERFACE; then
	mv i_plugin.h $I_PATH
	mv interface_impl.h $HDR_FILENAME
	mv interface_impl.cpp $SRC_FILENAME
else
	rm interface_impl.cpp interface_impl.h i_plugin.h
fi

echo "[SUCCESS] Your generated plugin could be found in ./Plugins/$NAME directory.
There is CMakeLists.txt file that could be opened with QtCreator."
