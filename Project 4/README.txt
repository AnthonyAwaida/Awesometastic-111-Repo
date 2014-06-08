Instructions:

	1. Load files into the corresponding directories
	2. "make install" in /server
	3. "make install" in /tools
	4. "reboot"
	5. "make" in /root
	6. Test "metacat" and "metatag" on existing files

Bugs:

	Problems:
		1. Entire data either does not get written or read entirely
		2. Metadata does not stay after reboot

	Where to fix it:
		/usr/src/servers/mfs/read.c
		rw_chunk()

	Side Effects:
		1. Cannot boot unless MINIX data storage size is increased (use 1024MB)
		2. At boot-up, zones will be missing and user will be prompted to remap

What is still needed:

	1. Test files as listed in the instructions
	2. Makefile for the entire minix directory
	