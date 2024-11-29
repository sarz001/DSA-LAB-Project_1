# File System Simulator

This is a simple file system simulator built in C++ that provides a command-line interface (CLI) for managing files and directories. The file system structure uses a **modified tree** for directories and **modified hash tables** for storing files and subdirectories efficiently.

![C++](https://img.shields.io/badge/Language-C%2B%2B-blue?style=flat-square) 

![DSA LAB](https://img.shields.io/badge/DSA%20LAB-blue?style=flat-square)
![BM23BTECH11020 | BM23BTECH11013](https://img.shields.io/badge/BM23BTECH11020%20%7C%20BM23BTECH11013-red?style=flat-square)

## Data Structures

The system uses the following data structures:

1. **Modified Tree (for Directories)**:  
   - The **Directory** class represents directories and maintains a tree structure through a parent pointer (`parent`) and subdirectories (`subDirs`).  
   - The parent pointer helps navigate up the directory tree (e.g., for the `cd ..` command), while the `subDirs` unordered map enables efficient searching for subdirectories.

2. **Modified Hash Tables (for Files and Subdirectories)**:  
   - **`files` (unordered_map<string, File*>)**: Stores files within the directory, allowing efficient file creation, deletion, and retrieval.
   - **`subDirs` (unordered_map<string, Directory*>)**: Stores subdirectories within the directory, enabling efficient directory navigation.

### Classes:

#### **File**
- **Attributes**:  
   - `name` (string): The name of the file.
   - `content` (string): The content of the file.
   
   - **Constructor**: Initializes a file with a name and optional content.

#### **Directory**
- **Attributes**:
   - `name` (string): The name of the directory.
   - `files` (unordered_map): A hash table of files in this directory.
   - `subDirs` (unordered_map): A hash table of subdirectories.
   - `parent` (Directory*): A pointer to the parent directory.

   - **Constructor**: Initializes a directory with a name and an optional parent pointer.

#### **FileSystem**
- **Attributes**:
   - `root` (Directory*): The root directory of the file system.
   - `currentDir` (Directory*): The current working directory.

### Key Methods:

#### **Directory Methods**:
- `createFile`: Creates a new file and stores it in the `files` hash table of the current directory.
- `deleteFile`: Deletes a file from the `files` hash table.
- `createDirectory`: Creates a subdirectory and stores it in the `subDirs` hash table.
- `deleteDirectory`: Deletes a subdirectory from the `subDirs` hash table (only if empty).
- `listDirectory`: Lists all files and subdirectories in the current directory.
- `changeDirectory`: Changes the current directory to the specified directory.
- `printCurrentDirectory`: Prints the full path of the current directory by traversing parent pointers.
- `saveToFile`: Saves the file system structure to a file.
- `loadFromFile`: Loads the file system structure from a saved file.
- `search`: Searches for a file or directory by name recursively.

---

## CLI Commands

### Command List

| **Command**           | **Description**                                                                 | **Data Structure Interaction** |
|-----------------------|---------------------------------------------------------------------------------|--------------------------------|
| **mkdir <dirName>**    | Creates a new directory with the specified name.                                | Adds a new entry in the `subDirs` hash table of the current directory (`Directory::subDirs`). |
| **touch <fileName>**   | Creates a new file with the specified name and optional content.                | Adds a new entry in the `files` hash table of the current directory (`Directory::files`). |
| **cat <fileName>**     | Displays the content of the specified file.                                     | Looks up the file in the `files` hash table of the current directory (`Directory::files`) and prints its content. |
| **rm <fileName>**      | Deletes the specified file.                                                     | Removes the file from the `files` hash table of the current directory (`Directory::files`) and frees its memory. |
| **rmdir <dirName>**    | Deletes the specified directory (if empty).                                     | Removes the directory from the `subDirs` hash table of the current directory (`Directory::subDirs`) if it is empty, and frees its memory. |
| **cd <dirName>**       | Changes the current working directory to the specified directory.               | Updates `currentDir` to point to the target directory, using the `subDirs` hash table of the current directory (`Directory::subDirs`) or the `parent` pointer for going up the tree. |
| **ls**                 | Lists the files and subdirectories in the current directory.                    | Iterates through the `files` hash table to list files and the `subDirs` hash table to list subdirectories of the current directory. |
| **pwd**                | Prints the full path of the current directory.                                  | Traverses the `parent` pointers of the current directory (`Directory::parent`) and prints the path by accumulating directory names. |
| **find <name>**        | Searches for a file or directory by name, printing its path if found.           | Recursively searches through the `subDirs` hash table for subdirectories and the `files` hash table for files, printing the path of any matches. |
| **printall**           | Prints all files and directories starting from the root directory.             | Recursively iterates over the entire directory tree, using the `subDirs` and `files` hash tables, and prints every directory and file starting from the root. |
| **save <filename>**    | Saves the entire file system structure (directories, files, and contents) to a file. | Recursively traverses the directory tree, writing directory and file names along with content (from `files` hash table) to the specified file. |
| **load <filename>**    | Loads the file system structure from a saved file.                             | Reads the file system from the specified file, populating the `subDirs` and `files` hash tables of each directory and reconstructing the tree structure. |

---

## Example Usage

```bash
>>> mkdir dir1
Directory created: dir1

>>> cd dir1
# Now we are in /dir1

>>> touch file1
File created: file1

>>> touch file2
File created: file2

>>> ls
Directory contents of dir1:
[FILE] file1
[FILE] file2

>>> cat file1
File content: 

>>> rm file2
File deleted: file2

>>> ls
Directory contents of dir1:
[FILE] file1

>>> mkdir subdir1
Directory created: subdir1

>>> cd subdir1
# Now we are in /dir1/subdir1

>>> touch file3
File created: file3

>>> ls
Directory contents of subdir1:
[FILE] file3

>>> cd ..
# Now we are back in /dir1

>>> rmdir subdir1
Directory deleted: subdir1

>>> ls
Directory contents of dir1:
[FILE] file1

>>> pwd
Current directory: /dir1

>>> find file1
/dir1/file1 [FILE]

>>> printall
Listing all files and directories starting from root:
[DIR] /
  [DIR] dir1
    [FILE] file1

>>> save filesystem.txt
File system saved to filesystem.txt

>>> exit
# Exiting the CLI

# Relaunching the CLI
>>> load filesystem.txt
File system loaded from filesystem.txt

>>> ls
Directory contents of dir1:
[FILE] file1

>>> cd /
# Now we are back to the root directory

>>> ls
Directory contents of /:
[DIR] dir1

```

##Conclusion

This file system simulator provides an easy-to-use interface for managing files and directories. It leverages a **tree structure** to manage directories and **hash tables** to store files and subdirectories efficiently. The implementation allows for common file system operations like creating and deleting files and directories, navigating directories, and saving/loading the file system to/from a file.

The core logic of the system is implemented in the `FileSystem` class, with directory and file management handled through efficient data structures. The CLI interface provides commands for interacting with the file system in a straightforward manner, similar to Unix-like file systems.

The simulator is a great tool for understanding how file systems work internally, focusing on the use of trees for directory structures and hash tables for fast access to files.

---

## How to Run

### Prerequisites

To run the project, you need to have a C++ compiler that supports C++11 or later (e.g., GCC or Clang).

### Steps to Run

1. **Clone the repository** (or download the `filesystem.cpp` file).
   
2. **Compile the C++ source code**:
   - Open a terminal in the directory where the `filesystem.cpp` file is located.
   - Run the following command to compile the program:
   
     ```bash
     g++ -std=c++11 -o filesystem filesystem.cpp
     ```

3. **Run the compiled program**:
   - After compilation, run the program with the following command:
   
     ```bash
     ./filesystem
     ```

4. **Interact with the File System**:
   - The program will start the command-line interface (CLI). You can now use the commands such as `mkdir`, `touch`, `cd`, `ls`, `pwd`, `save`, and `load` to interact with the file system.

5. **Exit the CLI**:
   - To exit the program, type `exit` at the command prompt.

### Example:

```bash
g++ -std=c++11 -o filesystem filesystem.cpp
./filesystem
>>> mkdir dir1
Directory created: dir1
>>> cd dir1
>>> touch file1
File created: file1
>>> ls
Directory contents of dir1:
[FILE] file1
>>> exit

