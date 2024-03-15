struct VFS {

    /*
    The vfs structures of all mounted file systems are organized as a singly linked list, collectively providing the information
    needed to maintain the entire hierarchical tree, as well as information about the actual file system, that does not change during operation.
    The first entry in the list is always the root filesystem.
    */

    struct VFS* vfs_next;             // Next filesystem on mount list
    struct VFS_operations* vfs_op;    // File System operations
    struct vnode* vfs_vnode_covered;  // vnode overlaid by the file system
    int vfs_flag;                     // Flags: read-only, SUID bit disabled, etc.
    int vfs_block_size;               // File system block size
    void* vfs_data;                   // Pointer to specific data related to the actual file system
};


struct VFS_operations {

    /*
    Possible file system operations are given below. Because they are highly architecture and implementation specific, 
    the vfs_op fields are populated with pointers to the corresponding functions of the actual file system when it is mounted.
    */

    int (*vfs_mount);                 // Mounts the file system. Typically the operation involves placing a superblock in memory and initializing an entry in the mount table
    int (*vfs_unmount);               // Disables the file system. The operation includes updating file system data on the drive (for example, synchronizing a disk superblock and its image in memory)
    int (*vfs_root);                  // Returns the root vnode of the filesystem
    int (*vfs_statistic_fs);          // Returns general information about the file system
    int (*vfs_sync);                  // Updates all cached file system data
    int (*vfs_file_id);               // Returns a file identifier (fid) that uniquely addresses a file in a given file system. The fid can, for example, be the inode number of a real file system
    int (*vfs_get_vnode);             // Returns a pointer to the vnode for the file on this file system addressed by file_id
};


struct VSW {

    /*
    To initialize and mount a real file system, UNIX maintains a File System Switch that addresses a procedural interface 
    for each type of file system supported by the kernel. 
    UNIX System V uses a global table for this, each element of which corresponds to a specific type of real file system.
    */

    char* vsw_name;
    int (*vsw_init);
    struct VFS_operations* vsw_vfs_op;
    long vsw_flag;
};


struct vnode {

    /*
    The interface for working with files is vnode (from virtual inode - virtual index descriptor).
    The vnode data structure is the same for all files, regardless of the type of actual file system where the file actually resides. 
    The vnode data contains information necessary for the operation of the virtual file system, as well as immutable characteristics of the file,
     such as the file type.
    */

    unsigned short v_flags;           // vnode flags
    unsigned short v_count;           // Number of links per vnode
    struct filock* v_filocks;         // File locks (do we need it?)
    struct vfs* v_vfs_mountered;      // Pointer to the mounted filesystem, if vnode is a mount point
    struct vfs* v_vsf_pointer;        // Pointer to the file system on which the file resides
    enum vtype v_type;                // vnode type: regular file, directory, special file etc.
    void* v_data;                     // Pointer to data related to the real file system
    struct vnode_operations v_op;     // vnode operations
};


struct vnode_operations {

    /*
    aka operations with files, directories and so on. --> Should be implemented in the Part 2
    */

    int (*vnode_open) ();             // Open vnode. If the operation involves creating a clone (reproduction), then the result will be a new vnode 
    int (*vnode_close) ();            // Close vnode
    int (*vnode_read) ();             // Reading data from a file addressed to a vnode
    int (*vnode_write) ();            // Writing to a file addressed to vnode
    int (*vnode_ioctl) ();            // Setting the control command
    int (*vnode_getaddr) ();          // Get vnode attributes
    int (*vnode_setaddr) ();          // Set vnode attributes. UID, GID, file size and access and modification times may be changed
    int (*vnode_access) ();           // Check access rights to the file addressed to vnode. This produces a mapping between the access attributes of UNIX files and the attributes of a real file system (for example, DOS)
    int (*vnode_io_lookup) ();        // Translate the file name to the corresponding vnode
    int (*vnode_create) ();           // Create a new file and its corresponding vnode
    int (*vnode_remove) ();           // Remove filename in specified vnode directory
    int (*vnode_link) ();             // Create a hard link between filename and vnode
    int (*vnode_mkdir) ();            // Create a new directory in the specified vnode directory
    int (*vnode_rmdir) ();            // Delete directory
    int (*vnode_readdir) ();          // Read directory entries addressed by vnode
    int (*vnode_symiink) ();          // Create a symbolic link between the new name and the name of a file located in the specified vnode directory
    int (*vnode_readlink) ();         // Reading a file - symbolic link
    int (*vnode_fsync) ();            // Synchronize file contents - write all cached data
    int (*vnode_inactive) ();         // Allow vnode removal because the number of references to the vnode from the virtual file system has become zero
};


