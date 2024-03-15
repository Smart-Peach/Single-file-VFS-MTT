#include <linux/pagemap.h>
#include <linux/fs.h>

#define RAMFS_MAGIC     0x858458f6

struct file_system_type {
         const char *name;                   // name to identify fs
         int fs_flags;  // flags with which fs must be mounted
         struct dentry *(*mount) (struct file_system_type *, int, const char *, void *); // reads superblock from the disk, unique to each filesystem
         void (*kill_sb) (struct super_block *);  // function that releases superblock  from memory
         struct module *owner;
         struct file_system_type * next;
         struct hlist_head fs_supers;  // list of all the superblocks associated with the fs
         struct lock_class_key s_lock_key;
         struct lock_class_key s_umount_key;
         //...
};


struct super_block {
        //...
        dev_t                   s_dev;              /* identifier */
        unsigned char           s_blocksize_bits;   /* block size in bits */
        unsigned long           s_blocksize;        /* block size in bytes */
        unsigned char           s_dirt;             /* dirty flag */
        loff_t                  s_maxbytes;         /* max file size */
        struct file_system_type *s_type;            /* filesystem type */
        struct super_operations *s_op;              /* superblock methods */
        //...
        unsigned long           s_flags;            /* mount flags */
        unsigned long           s_magic;            /* filesystem’s magic number */
        struct dentry           *s_root;            /* directory mount point */
        //...
        char                    s_id[32];           /* informational name */
        void                    *s_fs_info;         /* filesystem private info */
};

struct super_operations {
       //...
       int (*write_inode) (struct inode *, struct writeback_control *wbc);
       struct inode *(*alloc_inode)(struct super_block *sb);
       void (*destroy_inode)(struct inode *);

       void (*put_super) (struct super_block *);
       int (*statfs) (struct dentry *, struct kstatfs *);
       int (*remount_fs) (struct super_block *, int *, char *);
       //...
};

static const struct super_operations ramfs_ops = {
        .statfs         = simple_statfs,
        .drop_inode     = generic_delete_inode,
        .show_options   = ramfs_show_options,
};

static int ramfs_fill_super(struct super_block *sb, void *data, int silent)
{
        struct ramfs_fs_info *fsi;
        struct inode *inode;
        int err;

        save_mount_options(sb, data);

        fsi = kzalloc(sizeof(struct ramfs_fs_info), GFP_KERNEL);
        sb->s_fs_info = fsi;
        if (!fsi)
                return -ENOMEM;

        err = ramfs_parse_options(data, &fsi->mount_opts);
        if (err)
                return err;

        sb->s_maxbytes          = MAX_LFS_FILESIZE;
        sb->s_blocksize         = PAGE_SIZE;
        sb->s_blocksize_bits    = PAGE_SHIFT;
        sb->s_magic             = RAMFS_MAGIC;
        sb->s_op                = &ramfs_ops;
        sb->s_time_gran         = 1;

        inode = ramfs_get_inode(sb, NULL, S_IFDIR | fsi->mount_opts.mode, 0);
        sb->s_root = d_make_root(inode);
        if (!sb->s_root)
                return -ENOMEM;

        return 0;
}