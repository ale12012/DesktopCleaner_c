@Author Aleksander Augestad

--WINDOWS ONLY--

What it does:
	Hides/unhides icons on the desktop

How to install:
	gcc desktopcleaner.c -o desktopcleaner.exe
	
	Note: You must have the folder desktopcleaner_c in %programfiles%
	Note: It probably wont work without changing source code if you have a onedrive desktop.

Dependencies:
	Just libraries included with gcc

How it works:
	Reads status file
	staus file -> 0: 
		hides files logged in files.txt
		logs files on desktop in files.txt
		changes status.txt to 1
	status file ->
		shows files in files.txt
		changes status.txt to 0

	