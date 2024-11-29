#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <stack>
#include <fstream>
#include <sstream>

using namespace std;

// File class
class File {
public:
    string name;
    string content;

    File(string name, string content = "") : name(name), content(content) {}
};

// Directory class
class Directory {
public:
    string name;
    unordered_map<string, File*> files;
    unordered_map<string, Directory*> subDirs;
    Directory* parent;

    Directory(string name, Directory* parent = nullptr) : name(name), parent(parent) {}
};

// FileSystem class
class FileSystem {
private:
    Directory* root;
    Directory* currentDir;

public:
    FileSystem() {
        root = new Directory("/");
        currentDir = root;
    }

    // Create a new file
    void createFile(string fileName, string content = "") {
        if (currentDir->files.find(fileName) == currentDir->files.end()) {
            currentDir->files[fileName] = new File(fileName, content);
            cout << "File created: " << fileName << endl;
        } else {
            cout << "File already exists. Duplicate files are not allowed." << endl;
        }
    }

    // Read a file's content
    void readFile(string fileName) {
        if (currentDir->files.find(fileName) != currentDir->files.end()) {
            cout << "File content: " << currentDir->files[fileName]->content << endl;
        } else {
            cout << "File not found." << endl;
        }
    }

    // Delete a file
    void deleteFile(string fileName) {
        if (currentDir->files.find(fileName) != currentDir->files.end()) {
            delete currentDir->files[fileName];
            currentDir->files.erase(fileName);
            cout << "File deleted: " << fileName << endl;
        } else {
            cout << "File not found." << endl;
        }
    }

    // Create a new directory
    void createDirectory(string dirName) {
        if (currentDir->subDirs.find(dirName) == currentDir->subDirs.end()) {
            currentDir->subDirs[dirName] = new Directory(dirName, currentDir);
            cout << "Directory created: " << dirName << endl;
        } else {
            cout << "Directory already exists. Duplicate directories are not allowed." << endl;
        }
    }

    // Delete a directory (only if empty)
    void deleteDirectory(string dirName) {
        if (currentDir->subDirs.find(dirName) != currentDir->subDirs.end()) {
            if (currentDir->subDirs[dirName]->files.empty() && currentDir->subDirs[dirName]->subDirs.empty()) {
                delete currentDir->subDirs[dirName];
                currentDir->subDirs.erase(dirName);
                cout << "Directory deleted: " << dirName << endl;
            } else {
                cout << "Directory is not empty. Only empty directories can be deleted." << endl;
            }
        } else {
            cout << "Directory not found." << endl;
        }
    }

    // Change directory (cd)
    void changeDirectory(string dirName) {
        if (dirName == "..") {
            if (currentDir->parent != nullptr) {
                currentDir = currentDir->parent;
            } else {
                cout << "Already at the root directory." << endl;
            }
        } else if (dirName == "/") {
            currentDir = root;
        } else if (currentDir->subDirs.find(dirName) != currentDir->subDirs.end()) {
            currentDir = currentDir->subDirs[dirName];
        } else {
            cout << "Directory not found." << endl;
        }
    }

    // List contents of the current directory (ls)
    void listDirectory() {
        cout << "Directory contents of " << currentDir->name << ":" << endl;
        // List directories
        for (const auto& dir : currentDir->subDirs) {
            cout << "[DIR] " << dir.first << endl;
        }
        // List files
        for (const auto& file : currentDir->files) {
            cout << "[FILE] " << file.first << endl;
        }
    }

    // Show current directory path
    void printCurrentDirectory() {
        stack<string> path;
        Directory* temp = currentDir;

        while (temp != nullptr) {
            path.push(temp->name);
            temp = temp->parent;
        }

        cout << "Current directory: ";
        while (!path.empty()) {
            cout << path.top();
            path.pop();
            if (!path.empty()) cout << "/";
        }
        cout << endl;
    }

    // Save file system to a text file
    void saveToFile(const string& filename) {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            saveDirectoryRecursively(root, outFile, 0);
            outFile.close();
            cout << "File system saved to " << filename << endl;
        } else {
            cout << "Error opening file for writing." << endl;
        }
    }

    // Load file system from a text file
    void loadFromFile(const string& filename) {
        ifstream inFile(filename);
        if (inFile.is_open()) {
            root = new Directory("/");
            currentDir = root;
            loadDirectoryRecursively(root, inFile);
            inFile.close();
            cout << "File system loaded from " << filename << endl;
        } else {
            cout << "Error opening file for reading." << endl;
        }
    }

    // Recursive functions for saving/loading
    void saveDirectoryRecursively(Directory* dir, ofstream& outFile, int depth) {
        string indent(depth * 2, ' ');
        outFile << indent << "DIR " << dir->name << endl;

        for (const auto& file : dir->files) {
            outFile << indent << "  FILE " << file.first << " CONTENT " << file.second->content << endl;
        }

        for (const auto& subdir : dir->subDirs) {
            saveDirectoryRecursively(subdir.second, outFile, depth + 1);
        }
    }

    void loadDirectoryRecursively(Directory* dir, ifstream& inFile) {
        string line;
        while (getline(inFile, line)) {
            if (line.find("DIR") != string::npos) {
                string dirName = line.substr(line.find(" ") + 1);
                dir->subDirs[dirName] = new Directory(dirName, dir);
                loadDirectoryRecursively(dir->subDirs[dirName], inFile);
            } else if (line.find("FILE") != string::npos) {
                size_t fileNamePos = line.find("FILE") + 5;
                size_t contentPos = line.find("CONTENT") + 8;
                string fileName = line.substr(fileNamePos, line.find(" CONTENT") - fileNamePos);
                string content = line.substr(contentPos);
                dir->files[fileName] = new File(fileName, content);
            } else {
                break;
            }
        }
    }

    // Recursive search function (find)
    void search(string name, Directory* dir, string currentPath) {
        // Search for matching files or directories
        if (dir->name == name) {
            cout << currentPath << "/" << dir->name << " [DIR]" << endl;
        }
        for (const auto& file : dir->files) {
            if (file.first == name) {
                cout << currentPath << "/" << file.first << " [FILE]" << endl;
            }
        }

        // Recur for subdirectories
        for (const auto& subdir : dir->subDirs) {
            search(name, subdir.second, currentPath + "/" + subdir.first);
        }
    }

    // Print all files and directories from root recursively
    void printAllFromRoot() {
        cout << "Listing all files and directories starting from root:\n";
        printDirectoryRecursively(root, 0);  // Start from the root and depth 0
    }

    // Helper function for recursive printing of directories
    void printDirectoryRecursively(Directory* dir, int depth) {
        // Print indentation based on depth
        string indent(depth * 2, ' ');

        // Print directory name
        cout << indent << "[DIR] " << dir->name << endl;

        // List files in the directory
        for (const auto& file : dir->files) {
            cout << indent << "  [FILE] " << file.first << endl;
        }

        // Recursively list subdirectories
        for (const auto& subdir : dir->subDirs) {
            printDirectoryRecursively(subdir.second, depth + 1);
        }
    }

    // CLI interface for interaction
    void commandLine() {
    string command;
    while (true) {
        cout << ">>> ";
        getline(cin, command);

        if (command == "exit") {
            break;
        }

        // Parse the command
        vector<string> tokens;
        string token;
        istringstream stream(command);
        while (stream >> token) {
            tokens.push_back(token);
        }

        if (tokens.empty()) continue;

        // Command execution
        if (tokens[0] == "mkdir" && tokens.size() > 1) {
            createDirectory(tokens[1]);
        } else if (tokens[0] == "touch" && tokens.size() > 1) {
            createFile(tokens[1]);
        } else if (tokens[0] == "cat" && tokens.size() > 1) {
            readFile(tokens[1]);
        } else if (tokens[0] == "rm" && tokens.size() > 1) {
            deleteFile(tokens[1]);
        } else if (tokens[0] == "rmdir" && tokens.size() > 1) {
            deleteDirectory(tokens[1]);
        } else if (tokens[0] == "cd") {
            if (tokens.size() > 1) {
                changeDirectory(tokens[1]);
            } else {
                cout << "Please specify the directory to navigate to." << endl;
            }
        } else if (tokens[0] == "ls") {
            listDirectory();
        } else if (tokens[0] == "pwd") {
            printCurrentDirectory();
        } else if (tokens[0] == "find" && tokens.size() > 1) {
            search(tokens[1], currentDir, ".");
        } else if (tokens[0] == "printall") {
            printAllFromRoot();
        } else if (tokens[0] == "save" && tokens.size() > 1) { // Save command
            saveToFile(tokens[1]);
        } else if (tokens[0] == "load" && tokens.size() > 1) { // Load command
            loadFromFile(tokens[1]);
        } else {
            cout << "Invalid command!" << endl;
        }
    }
}

};

// Main function for testing the CLI
int main() {
    FileSystem fs;
    fs.commandLine();  // Launch CLI for user interaction

    return 0;
}