# First Part:
   
## 1. Interpreter:

Some basic commands to implement: 
</br>

| <div style="width:398px">Public file commands</div>     | <div style="width:315px">Public directory commands</div>|
|:-------------------------------------------------------:| :------------------------------------------------------:|

| Command name          | Syntax                          | Command name          | Syntax                          |
| --------------------- | ------------------------------- |-----------------------|---------------------------------|
| Create                | create <file_name>              | Create dir            | crtdir <dir_name>               |
| Delete                | delete <file_name>              | Delete dir            | deldir <dir_name>               |
| Edit                  | edit <file_name>                | Read dir              | rdir <dir_name>                 |
| Read                  | read <file_name>                | Rename dir            | rndir <dir_name> "text"         |
| Write                 | write <file_name> "text"        | Link dir              | ldir <dir_name>                 |
| Append                | append <file_name> "text"       | Unlink dir            | uldir <dir_name>                | 
| Seek (search in file) | seek <file_name>                |                       |                                 |
| Rename                | rn <file_name> <new_file_name>  |                       |                                 |
| Move file             | mv <file_name> <new_file_path>  |                       |                                 |

</br>

|<div style="width:399px">Private file commands</div>     | <div style="width:315px">Private directory commands</div>|
|:-------------------------------------------------------:| :-------------------------------------------------------:|

| Command name <        | <div style="width:235px">Syntax</div>| Command name     | <div style="width:170px">Syntax</div>|
| --------------------- | ------------------------------- |-----------------------|--------------------------------|
| Open                  | - <file_name>                   | Open dir              | - <dir_name>                   |
| Close                 | - <file_name>                   | Close dir             | - <dir_name>                   |

</br>

## 2. Location in memory:  

|info                   | Boot sector           | Superblock            | Information about free blocks     | i-list    | root dir   | file's data   |
| --------------------- | --------------------- |-----------------------|-----------------------------------|-----------|------------|---------------|
| size  (bytes)         | 1024                  | 1024                  | 800 000                           | 800 000   | 512        |               |
| implementation           |  -                  | Superblock structure             | bitset                         | hash-table| Dentry structure         |               |

</br>

- ***Superblock:***

     Contains information about file system in general. It is needed in case of crash of file system. (to store important data)

     1. Max file size
     2. Fs type (in our case - linear)
     3. Fs size including superblock itself, i-list and blocks of data storage (1 073 741 824)
     4. i-list size 
     5. Amount of free blocks available to store data
     6. Amount of free i-nodes available to store data
     7. Size of block (1024)
     8. List of free blocks 

- ***Information about free blocks:***

     1. Implemented via bit table --> bit sequence
     2. Size equals to number of blocks
     3. Address of required block is calculated in that way:
          - we go through the sequance (suggest linear) and count the bit's index
          - then calculate: `2048 + sizeof(bit_table) + sizeof(i-nodes) + sizeof(root_dir) + bit_ind * sizeof(block)`

- ***i-list:***
     1. i-list is a list of i-nodes
     2. i-node:
          Describes file/directory. Contains next fields:
          - unique number of i-node (aka magic number)
          - 2 optional bits (for permissions)
          - Number of references to file
          - Identificator of owner/user and group-owner
          - Size of file in bytes (for special files it contains MSB and LSB)
          - time of last access to the file
          - time of last modification
          - time of last modification of i-node
          - Array of storage block addresses

     3. Implemented via hash table:
          - open addressing
          - think about hash-function
          - key - hash, value - i-node
          - In case of fs crash it loads into memory

# Part 2
## File System Basic Commands:

### TODO: interpretor and context, friend commands for FileSystem (Superblock)

  1. Create file:
     * create inode
     * add too InodeMap 
     * update Superblock
  2. Delete file:
     * check if file exists
     * delete inode in InodeMap
     * update inode in Syperblock
     * resolve problem with garbage in blocks
  3. Open file:
     * get addresses of blocks
  4. Close file:
     * load data into bin file
  5. Read file:
     * open file
     * read file content from binary file  #TODO: read_from_memory(block), read_from_memory(block[])
     * print file content to console
  7. Write to file:
     * inode = InodeMap.get_inode()
     * get last block and size of file (to define the end of file) #TODO: get_end_of_file()
     * check size of data to write (count amount of extra blocks)
     * get addresses of free blocks from Superblock
     * update inode in Superblock and InodeMap
     * load input data to bin file (close)
  8. Edit file:
     * get position to write data into file
     * write(pos, data)
  9. Update interpretor