/*
The inode (index node) keeps information about a file in the general sense (abstraction): 
regular file, directory, special file (pipe, fifo), block device, character device, link, or anything that can be abstracted as a file.
The inodes on disk are generally grouped into a specialized area (inode area) separated from the data blocks area;
Each inode is generally identified by a number. 
*/