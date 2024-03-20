1. First Part:
   
     1. Interpretor:
          Some basic commands to implement

          | <div style="width:398px">Public file commands</div>     | <div style="width:278px">Public directory commands</div>|
          |:-------------------------------------------------------:| :------------------------------------------------------:|

          | Command name          | Syntax                          | Command name          | Syntax                         |
          | --------------------- | ------------------------------- |-----------------------|--------------------------------|
          | Create                | create <file_name>              | Create dir            | crtdir <dir_name>              |
          | Delete                | delete <file_name>              | Delete dir            | deldir <dir_name>              |
          | Edit                  | edit <file_name>                | Read dir              | rdir <dir_name>                |
          | Read                  | read <file_name>                | Rename dir            | rndir <dir_name> "text"        |
          | Write                 | write <file_name> "text"        | Link dir              | ldir <dir_name>                |
          | Append                | append <file_name> "text"       | Unlink dir            | uldir <dir_name>               | 
          | Seek (search in file) | seek <file_name>                |                       |                                |
          | Rename                | rn <file_name> <new_file_name>  |                       |                                |
          | Move file             | mv <file_name> <new_file_path>  |                       |                                |

          
          |<div style="width:398px">Private file commands</div>     | <div style="width:278px">Private directory commands</div>|
          |:-------------------------------------------------------:| :-------------------------------------------------------:|

          | Command name <        | <div style="width:235px">Syntax</div>| Command name     | <div style="width:132px">Syntax</div>|
          | --------------------- | ------------------------------- |-----------------------|--------------------------------|
          | Open                  | - <file_name>                   | Open dir              | - <dir_name>                   |
          | Close                 | - <file_name>                   | Close dir             | - <dir_name>                   |


   
    1. Init:
         - registration FS
         - call interpretor

    2. Structures:
         - TODO: do research what structures we need
         - File descriptor
         - Structure of pointers to functions 

   What should we do:
     - pseudo_fs.bin - address space
     - Structures:
          - Superblock: contains information of fs in general (max file size, max blocks amount and so on). It will lay in first 1024 bytes of address space to save important information of our fs
          - File: contain information about exact file. Some useful stuff: address of file, sizeof file, type of information (aka text, jpg and so on), the date the file was created or modified, and the file's permissions (e.g., whether it is readable, writable, or executable).
     - Understand how data should settle down in our binary file --> directories???
     - Массив индексных дескрипторов (ilist): contains metadata of all files 
     - Inode: describes exact file 
     - File descriptor table

     3. Location in memory:  


          |info                   | Boot sector           | Superblock            | Information about free blocks     | i-list    | root dir   | file's data |
          | --------------------- | --------------------- |-----------------------|-----------------------------------|-----------|----------|-------------|
          | size  (bytes)         | 1024                  | 1024                  |                                   |           |          |             |
          | realisation           |  wtf                  | structure             | bit table                         | hash-table| hz     | |


     Superblock:

          Contains information about file system in general. It is needed in case of crash of file system. (to store important data)

               - Max file size
               - Fs type (in our case - linear)
               - Fs size including superblock itself, i-list and blocks of data storage (1 073 741 824)
               - i-list size 
               - Amount of free blocks available to store data
               - Amount of free i-nodes available to store data
               - Size of block (1024)
               - List of free blocks 

     Information about free blocks:

          1. Implemented via bit table --> bit sequence
          2. Size equals to number of blocks
          3. Address of required block is calculated in that way:
               - we go through the sequance (suggest linear) and count the bit's index
               - then calculate: 2048 + sizeof(bit_table) + sizeof(i-nodes) + sizeof(root_dir) + bit_ind * sizeof(block)

     i-list:
          1. i-list is a list of i-nodes
          2. i-node:
               Describes file/directory. Contains next fields
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
