<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>File System Simulator</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            line-height: 1.6;
            margin: 20px;
            background-color: #f4f4f4;
            color: #333;
        }
        h1, h2 {
            color: #5c6bc0;
        }
        code {
            background-color: #e0e0e0;
            padding: 2px 6px;
            border-radius: 4px;
        }
        pre {
            background-color: #333;
            color: #f5f5f5;
            padding: 15px;
            border-radius: 6px;
            overflow: auto;
        }
        table {
            width: 100%;
            border-collapse: collapse;
            margin: 20px 0;
        }
        th, td {
            padding: 10px;
            text-align: left;
            border: 1px solid #ddd;
        }
        th {
            background-color: #5c6bc0;
            color: white;
        }
        tr:nth-child(even) {
            background-color: #f9f9f9;
        }
        .command {
            background-color: #2196F3;
            color: white;
            padding: 5px 10px;
            border-radius: 4px;
        }
        .example {
            background-color: #388E3C;
            color: white;
            padding: 5px 10px;
            border-radius: 4px;
        }
    </style>
</head>
<body>
    <h1>File System Simulator</h1>
    <p>This is a simple file system simulator built in C++ that implements a hierarchical file structure using modified trees and hash tables. The simulator includes basic file and directory management features such as creating files, reading their contents, deleting files, changing directories, and more. It is operated via a command-line interface (CLI).</p>

    <h2>Data Structures</h2>
    <p>The file system uses two main data structures to manage files and directories:</p>
    <ul>
        <li><strong>Modified Tree (for directories):</strong> Each directory is represented as a node with pointers to its subdirectories, which form a tree structure.</li>
        <li><strong>Modified Hash Table (for files):</strong> Each directory stores its files in an unordered map (hash table) for efficient file storage and retrieval.</li>
    </ul>

    <h2>CLI Commands</h2>
    <p>Below is a list of the available commands in the file system simulator CLI:</p>

    <table>
        <thead>
            <tr>
                <th>Command</th>
                <th>Description</th>
                <th>Data Structure Interaction</th>
            </tr>
        </thead>
        <tbody>
            <tr>
                <td><code class="command">mkdir &lt;dirName&gt;</code></td>
                <td>Creates a new directory with the specified name.</td>
                <td>Adds a new entry in the <code>subDirs</code> hash table of the current directory.</td>
            </tr>
            <tr>
                <td><code class="command">touch &lt;fileName&gt;</code></td>
                <td>Creates a new file with the specified name and optional content.</td>
                <td>Adds a new entry in the <code>files</code> hash table of the current directory.</td>
            </tr>
            <tr>
                <td><code class="command">cat &lt;fileName&gt;</code></td>
                <td>Displays the content of the specified file.</td>
                <td>Looks up the file in the <code>files</code> hash table and prints its content.</td>
            </tr>
            <tr>
                <td><code class="command">rm &lt;fileName&gt;</code></td>
                <td>Deletes the specified file.</td>
                <td>Removes the file from the <code>files</code> hash table and frees its memory.</td>
            </tr>
            <tr>
                <td><code class="command">rmdir &lt;dirName&gt;</code></td>
                <td>Deletes the specified directory (if empty).</td>
                <td>Removes the directory from the <code>subDirs</code> hash table of the current directory if it is empty, and frees its memory.</td>
            </tr>
            <tr>
                <td><code class="command">cd &lt;dirName&gt;</code></td>
                <td>Changes the current working directory to the specified directory.</td>
                <td>Updates <code>currentDir</code> to point to the target directory using the <code>subDirs</code> hash table or the <code>parent</code> pointer.</td>
            </tr>
            <tr>
                <td><code class="command">ls</code></td>
                <td>Lists the files and subdirectories in the current directory.</td>
                <td>Iterates through the <code>files</code> hash table for files and <code>subDirs</code> for subdirectories.</td>
            </tr>
            <tr>
                <td><code class="command">pwd</code></td>
                <td>Prints the full path of the current directory.</td>
                <td>Traverses the <code>parent</code> pointers of the current directory and prints the path.</td>
            </tr>
            <tr>
                <td><code class="command">find &lt;name&gt;</code></td>
                <td>Searches for a file or directory by name.</td>
                <td>Recursively searches the <code>files</code> and <code>subDirs</code> hash tables for matches.</td>
            </tr>
            <tr>
                <td><code class="command">printall</code></td>
                <td>Prints all files and directories starting from the root directory.</td>
                <td>Recursively traverses the directory tree, printing all directories and files.</td>
            </tr>
            <tr>
                <td><code class="command">save &lt;filename&gt;</code></td>
                <td>Saves the entire file system structure to a file.</td>
                <td>Recursively writes directory and file names, including contents, to the specified file.</td>
            </tr>
            <tr>
                <td><code class="command">load &lt;filename&gt;</code></td>
                <td>Loads the file system structure from a saved file.</td>
                <td>Reads the file system from the specified file and reconstructs the structure by populating <code>subDirs</code> and <code>files</code>.</td>
            </tr>
        </tbody>
    </table>

    <h2>Example Usage</h2>
    <p>Here is an example of how to use all the available commands:</p>

    <pre>
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
    </pre>

    <h2>Conclusion</h2>
    <p>This file system simulator leverages a <strong>tree structure</strong> for directories and <strong>hash tables</strong> for efficient storage and retrieval of files and subdirectories. Each function directly interacts with these data structures to manage the file system.</p>
</body>
</html>
