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

   1. Architecture:

      


         
