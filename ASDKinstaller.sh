#!/bin/bash

# See LICENSE file for copyright and license details.

if [ -d $1 ]
then
	cd $1
	echo "Downloading the latest SDK tools..."
	curl -o sdktools.zip https://dl.google.com/android/repository/commandlinetools-linux-6200805_latest.zip
	if [ $? -ne 0 ]
	then
		echo
		echo "Couldn't download the SDK tools. Make sure you are connected to the internet and try again."
		echo "Press Enter/Return to exit."
		read
		exit 1
	else
		echo "Unzipping the SDK tools..."
		unzip sdktools.zip -d cmdline-tools
		if [ $? -ne 0 ]
		then
			echo "Make sure you have unzip installed and try again."
			echo "Press Enter/Return to exit."
			read
			exit 1
		else
			rm -rf sdktools.zip
			cd cmdline-tools
			mv tools latest
			echo "PATH=$PATH:$1/cmdline-tools/latest/bin"
			exit 0
		fi
	fi
	echo "Installation successfull. Press Enter/Return to exit."
	read
	exit 0
else
	echo "Invalid directory. Please try again."
	echo "Press Enter/Return to exit."
	read
	exit 1
fi

