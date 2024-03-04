# Virtual File System MTT

## Brilliant, incredible, amazing plan:

### Part 0:
1. Setup environment (not to break computers) --> cygwin(?) or VirtualBox

### Part 1: File System Setup and Initialization
1. File System Initialization:
    - Create executable file
    - Interpret console commands (parser)
    - Initialize the file system structures and metadata for managing the single file within the VFS (Connect VFS and FS + buffer cache)
    - Structure which filled with pointers to corresponding FS driver functions (esp_vfs_t)
    - File Descriptors: mapping global file descriptors to VFS driver indexes registered in the array.
    - Master File Table: Contains metadata of file
    - Registration - we should register FS we work with. Kinda:
```
esp_vfs_t myfs = {
            .flags = ESP_VFS_FLAG_DEFAULT,
            .write = &myfs_write,
            .open = &myfs_open,
            .fstat = &myfs_fstat,
            .close = &myfs_close,
            .read = &myfs_read,
            };
ESP_ERROR_CHECK(esp_vfs_register("/data", &myfs, NULL));
```

   
2. File System Read and Write Operations:
    - Operations: read and write operations (to interact with the single file).
    - Functions: opening, closing, and modifying the file content.

### Part 2: File System Operations and Management
1. File Manipulation Operations:
    - Operations: creating, deleting, copying, moving, and renaming the single file.
    - Functions: modifying file properties and contents.

2. File System Security and Permissions:
    - Security mechanisms: file access control (security descriptor), permissions, and ownership settings.

3. File System Navigation and Search:
    - Functions: navigating, accessing, and searching.
    - Maybe retrieval mechanisms.

### TODO:
1. Error Handling and Logging:
    - Handle exceptions, errors.
    - Log file system activities.

2. User Interface and Interaction:
    - UI.
    - Should it be like Far? idk.


### Optional: 
1. File Metadata Handling:
    - Manage file metadata  (file attributes, permissions etc).
    - Mechanisms to store and update file metadata.
    - Possible entities for metadata:
        - Superblock
        - inode
        - file
        - dentry
    - Metadata interact using (maybe) next subsystems: 
        - dentry cache
        - inode cache
        - buffer cache

2. The structure includes several main components that allow you to abstract from a specific system and provide a unified interface for working with files and directories. These include:
    - interfaces;
    - file table;
    - file descriptor table;
    - drivers;
    - cache;
    - system calls.

### Nice and useful links:
1. OSDev:
https://wiki.osdev.org/VFS

2. Wikipedia: 
https://en.wikipedia.org/wiki/Virtual_file_system

3. LINUX LAB WITH EXAMPLES!!!!:
https://linux-kernel-labs.github.io/refs/pull/165/merge/labs/filesystems_part1.html
https://linux-kernel-labs.github.io/refs/pull/165/merge/labs/filesystems_part2.html

4. How to write custom vfs:
https://support.kaspersky.ru/help/KCE/1.1/en-US/vfs_backends.htm

5. Really useful: 
https://www.quora.com/How-can-I-implement-a-virtual-file-system-using-C-or-C++-Can-you-please-share-some-code

6. Our google file:
https://docs.google.com/document/d/1NtjZ_1by78jzoXFTpV_xjDl8-KFVUTvta4vsJ2M6H_U/edit?pli=1
