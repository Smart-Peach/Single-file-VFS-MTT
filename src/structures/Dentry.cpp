#include "../includes/Dentry.hpp"

// // Allocates the root dentry. 
// // It is generally used in the function that is called to read
// // the superblock (fill_super), which must initialize the root directory. 
// bool Dentry::d_make_root() { }

// // This function will be used when creating/loading
// // a new inode that does not have a dentry associated with it
// // and has not yet been introduced to the hash table of inodes
// bool Dentry::d_associate_inode() { }

// // The lighter version of the previous call, in which the dentry 
// // was previously added in the hash table.
// bool Dentry::d_create_dentry() { }