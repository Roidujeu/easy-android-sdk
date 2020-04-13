#!/bin/bash

# See LICENSE file for copyright and license details.

case $1 in
	a)
		echo "This plugin requires the following: >=JDK 1.8, >=Vim 7.1, Eclipse 4.8.x, Python 2.7 or 3.x, make, and gcc."
		echo -n "Enter your .vimrc location with full path: "
		read vimrcLoc
		if [ -f "$vimrcLoc/.vimrc" ]
		then
			echo "set nocompatible" >> $vimrcLoc/.vimrc
			echo "filetype plugin indent on" >> $vimrcLoc/.vimrc
		else
			echo "Invalid directory/file. Press Enter/Return to exit."
			read
			exit 1
		fi
		echo "Downloading required components for vim....."
		curl -o eclim.bin "https://github.com/ervandew/eclim/releases/download/2.8.0/eclim_2.8.0.bin"
		if [ $? -eq 0 ]
		then
			./eclim.bin
			exit 0
		else
			echo "Couldn't download Eclim. Press Enter/Return to exit."
			read
			exit 1
		fi
		;;
	c)
		echo -n "Choose between 32 or 64 (bits): "
		read bitsy
		if [ $bitsy -eq 32 -o $bitsy -eq 64 ]
		then
			if [ $bitsy -eq 32 ]
			then
				echo "Sorry, Eclipse doesn't provide 32-bit packages now. Press Enter/Return to exit."
				read
				exit 1
			else
				echo "Choose the directory where you want to install eclipse: "
				read eclipseLoc
				if [ -d $eclipseLoc ]
				then
					cd $eclipseLoc
					echo "Downloading Eclipse tools for Java....."
					curl -o eclipseTools.tar.gz "http://eclipse.mirrors.estointernet.in/technology/epp/downloads/release/2020-03/R/eclipse-java-2020-03-R-linux-gtk-x86_64.tar.gz"
					if [ $? -eq 0 ]
					then
						tar -xf eclipseTools.tar.gz
						rm -rf eclipseTools.tar.gz
						exit 0
					else
						echo "Couldn't download Eclim. Press Enter/Return to exit."
						read
						exit 1
					fi
				else
					echo "Invalid directory. Press Enter/Return to exit."
					read
					exit 1
				fi
			fi
		else
			echo "Invalid choice. Press Enter/Return to exit."
			read
			exit 1
		fi
		;;
esac
