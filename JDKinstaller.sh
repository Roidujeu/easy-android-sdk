#!/bin/bash

# See LICENSE file for copyright and license details.

if [ -d "$1" ]
then
	ping -qc 1 www.google.com > /dev/null 
	if [ $? -ne 0 ]
	then
		echo "Not connected to internet. Please try again. Press Enter/Return to exit."
		read
		exit 1
	else
		echo "Downloading OpenJDK 13..."
		cd $1
		curl -o openjdk_13.tar.gz https://download.java.net/java/GA/jdk13.0.2/d4173c853231432d94f001e99d882ca7/8/GPL/openjdk-13.0.2_linux-x64_bin.tar.gz
		if [ $? -ne 0 ]
		then
			echo "Couldn't download OpenJDK. Please try again. Press Enter/Return to exit."
			read
			exit 1
		else
			echo "Done."
			echo "Extracting the archive..."
			tar -xf openjdk_13.tar.gz
			if [ $? -ne 0 ]
			then
				echo "Couldn't extract the OpenJDK folder. Make sure you have tar installed. Press Enter/Return to exit."
				read
				exit 1
			else
				echo "Done."
				cd jdk-13.0.2
				cd bin
				echo "Adding the current directory to PATH variable..."
				loc=`pwd`
				echo "PATH=$PATH:$loc" >> ~/.bashrc
				echo "Done."
				echo "Creating the JAVA_HOME variable..."
				echo "JAVA_HOME=$loc" >> ~/.bashrc
				echo "Installation successfull. Press Enter/Return to exit."
				exit 0
			fi
		fi
	fi
else
	echo "Invalid directory. Press Enter/Return to exit."
	read
	exit 1
fi
