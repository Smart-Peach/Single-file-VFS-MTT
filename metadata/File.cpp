/*
File is the component of the file system model that is closest the user. 
The structure exists only as a VFS entity in memory and has no physical correspondent on disk.

While the inode abstracts a file on the disk, the file structure abstracts an open file.
From the point of view of the process, the file entity abstracts the file.
From the point of view of the file system implementation, however, the inode is the entity that abstracts the file.
*/