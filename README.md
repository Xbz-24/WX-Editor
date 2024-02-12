## WX-Editor 
lightweight code editor built using the wxWidgets framework, has nix shell for cross platform easy compilation.

## Overview
wxEditor is a lightweight, cross-platform text editor I am designing for it to replace my main C++ editor. It is built using the wxWidgets framework to provide a native look and feel on each platform (Windows, OSX and Artix/NixOS, the platforms I use).

### - First Milestone - Scintilla Widget Integration 
![image](https://github.com/Xbz-24/editor-wx/assets/68678258/75d73f0c-b439-43f0-a2fd-811c355a2e3c)
### - Intermediate Milestone - Designing the UI using wxFormBuilder
![image](https://github.com/Xbz-24/WX-Editor/assets/68678258/2c9f9e4a-7ac2-417f-8421-c5f4a8ae9cf1)
### - Second Milestone - Implementing the UI from the wxFormBuilder XML file 
![image](https://github.com/Xbz-24/WX-Editor/assets/68678258/89b43d81-3a54-4fb3-bfbc-69a6a0695219)
### - Third Milestone - Redimention of some sizers from layout and adding custom Logo
![image](https://github.com/Xbz-24/WX-Editor/assets/68678258/ec0d2146-20aa-444a-a179-85cab1101fb2)
### - Intermediate Milestone - Introduction of the UML class diagram representation
![image](https://github.com/Xbz-24/WX-Editor/assets/68678258/759aa569-79c9-4a0a-8473-9579848f47cb)

# - Description of the project
## Features
- Text editing
- C++ Syntax highlighting
- Dark and Light mode
- Find and Replace
- Undo and Redo
- File operations: Open, Save, and Create New files

## Getting Started

### Prerequisites
- C++ Compiler (GCC, Clang, MSVC)
- wxWidgets library
- Windows: vcpkg
- OSX: Homebrew, and Xcode-Command-Line-Tools 

### Building the Application
1. **Clone the repository:**
   ```
   git clone https://github.com/Xbz-24/WX-Editor.git
   ```

2. **Build the project: preferred way will always be using nix.**
      - NixOS:
      ```
      nix-shell
      mkdir build && cd build
      cmake -S .. -B .
      ```
      - Artix:
      ```
        sudo pacman -S wxgtk3 wxgtk-common wxgtk3-contrib wxgtk3-docs wxgtk3-i18n wxgtk3-media wxgtk3-unicode wxgtk3-stc wxgtk3-tools wxgtk3-webview wxgtk3-xrc
        mkdir build && cd build
        cmake -S .. -B .
      ```
     - Windows: use vcpkg to install wxWidgets and other dependencies
      ```
      vcpkg integrate install
      mkdir build && cd build
      cmake -S .. -B .
      ```
    - OSX:
     ```
       brew install wxwidgets
       mkdir build && cd build
       cmake -S .. -B .
     ```

3. **Run the application:**
   ```
   ./editor
   ```

### Usage
Launch the application and use the menu or toolbar to perform actions like opening a file, saving changes, or toggling the editor theme.

## Contributing
Contributions to wxEditor are always welcome. Please feel free to submit pull requests or open issues to discuss proposed changes.

## License
This project is licensed under the MIT License - see the license file for details.

## Acknowledgments
- Built using the [wxWidgets](https://www.wxwidgets.org/) framework.
