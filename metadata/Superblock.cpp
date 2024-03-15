/*
The superblock stores the information needed for a mounted file system.
In the case of disk file systems, the superblock has a correspondent in the first block of the disk. (Filesystem Control Block).
In VFS, all superblocks of filesystems are retained in a list of structures of type struct super_block and the methods in structures of type struct super_operations.
*/

struct Super_block {
        /*
        dev_t --> is used for device ID, integer type
        loff_t --> long off_t, off_t is used for describing file sizes
        */
        dev_t                   s_dev;              // identifier 
        unsigned char           s_blocksize_bits;   // block size in bits 
        unsigned long           s_blocksize;        // block size in bytes 
        unsigned char           s_dirt;             // dirty flag 
        loff_t                  s_maxbytes;         // max file size 
        struct file_system_type *s_type;            // filesystem type 
        struct super_operations *s_op;              // superblock methods
        //...
        unsigned long           s_flags;            // mount flags 
        unsigned long           s_magic;            // filesystem’s magic number
        struct dentry           *s_root;            // directory mount point
        //...
        char                    s_id[32];           // informational name
        void                    *s_fs_info;         // filesystem private info
};

struct Super_block_operations {
       //...
       int (*write_inode) (struct inode *, struct writeback_control *wbc);
       struct inode *(*alloc_inode)(struct super_block *sb);
       void (*destroy_inode)(struct inode *);

       void (*put_super) (struct super_block *);
       int (*statfs) (struct dentry *, struct kstatfs *);
       int (*remount_fs) (struct super_block *, int *, char *); // is called when the kernel detects a remount attempt (mount flag MS_REMOUNTM)
       //...
};