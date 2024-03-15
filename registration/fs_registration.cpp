#define RAMFS_MAGIC     0x858458f6

struct file_system_type {
    /* The structure describing a particular file system */
         const char *name;                                                               // name to identify fs
         int fs_flags;                                                                   // flags with which fs must be mounted
         struct dentry *(*mount) (struct file_system_type *, int, const char *, void *); // function that reads superblock from the disk, unique to each filesystem
         void (*kill_sb) (struct super_block *);                                         // function that releases superblock from memory
         struct module *owner;                                                           // THIS_MODULE for file systems implemented in modules, and NULL if they are written directly into the kernel
         struct file_system_type * next;
         struct hlist_head fs_supers;                                                    // list of all the superblocks associated with the fs
         struct lock_class_key s_lock_key;
         struct lock_class_key s_umount_key;
         //...
};