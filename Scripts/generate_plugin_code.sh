#!/bin/bash

read -p 'Specify name of your plugin: ' NAME
if [[ -e "./Plugins/$NAME" ]]; then
	echo 'Plugin with same name already exists in ./Plugins!'
	exit
fi

read -p "Your plugin is graphical user interface for other plugin? (y/n) " IS_UI
if [[ $IS_UI == 'n' ]]; then
	read -p "Are you planning to provide some of your plugin's functionality to other plugins? (y/n) " HAS_INTERFACE
	if [[ $HAS_INTERFACE == 'y' ]]; then
		I_NAME="I$NAME"
		read -p "Specify name of your plugin's interface (press Enter to use suggested name: $I_NAME): "
		if [[ -n $RES ]]; then
			I_NAME=$RES
		fi
		I_FILENAME=$(echo "${I_NAME}.h" | sed -E 's/^I/i/' | 
			sed -E 's/([A-Z][a-z])/_\1/g' |
			sed -E 's/([a-z])([A-Z])/\1_\2/g' |
			tr '[:upper:]' '[:lower:]')
		read -p "Specify filename of your plugin's interface (press enter to use suggested name: $I_FILENAME): " RES
		if [[ -n $RES ]]; then
			I_FILENAME=$RES
		fi
		I_PATH="../../Interfaces/Utility/$I_FILENAME"
		if [[ -e $I_PATH ]]; then
			echo 'Interface with same name already exists in ./Plugins!'
			exit
		fi
		HDR_FILENAME=$(echo "$I_FILENAME" | sed -E 's/^i_(.+)/\1/')
		SRC_FILENAME=$(echo "$I_FILENAME" | sed -E 's/^i_(.+).h/\1.cpp/')
	fi
else
	read -p "Your plugin will use:
1 - QML(recommended)
2 - QWidjets
Type option number: " UI_TYPE
	if [[ $UI_TYPE == '1' ]]; then
		REF_FILENAMES=($(ls -1 Interfaces/Utility | sort))
		echo "Your plugin is graphical user interface of other plugin. Please, choose name of file that contains interface of that plugin:"
		for ((i = 0; i < ${#REF_FILENAMES[@]}; i++)); do
			echo "$i: ${REF_FILENAMES[i]}"
		done
		read -p 'File index: ' INDEX
		REF_FILENAME=${REF_FILENAMES[INDEX]}
		REF=$(grep -oE 'INTERFACE(.+),' Interfaces/Utility/$REF_FILENAME | sed -E 's/INTERFACE\((.+)\,/\1/')
		REF_FILENAME="../../Interfaces/Utility/$REF_FILENAME"
	fi
fi

cp -r ./Scripts/PluginTemplate ./Plugins/$NAME
cd ./Plugins/$NAME
DESC='Author of this plugin have nothing to say'

for f in $(ls | grep -E '\.(txt|cpp|h|qml|json)$'); do
	if [[ $IS_UI == 'n' ]]; then
		sed -i -E "/@(WID|QML|UI)/d" $f
	else
		sed -i -E "s/@UI@//g" $f
		if [[ $UI_TYPE == '1' ]]; then
			sed -i -E "s/@QML@//g" $f
			sed -i -E "/@WID@/d" $f
		else
			sed -i -E "s/@WID@//g" $f
			sed -i -E "/@QML@/d" $f
		fi
	fi
	if [[ -n $I_PATH ]]; then
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


if [[ $IS_UI == 'n' ]]; then
	rm form.qml form.ui res.qrc
else
	if [[ $UI_TYPE == '1' ]]; then
		rm form.ui
	else
		rm form.qml res.qrc
	fi
fi
if [[ -n $I_PATH ]]; then
	mv i_plugin.h $I_PATH
	mv interface_impl.h $HDR_FILENAME
	mv interface_impl.cpp $SRC_FILENAME
else
	rm interface_impl.cpp interface_impl.h i_plugin.h
fi

echo "[SUCCESS] Your generated plugin could be found in ./Plugins/$NAME directory.
There is CMakeLists.txt file that could be opened with QtCreator."
