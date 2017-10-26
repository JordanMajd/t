# T ![Version 1.0.0](https://img.shields.io/badge/Version-1.0.0-green.svg)

[![BSD 2-clause licensed](https://img.shields.io/badge/license-BSD-blue.svg)](/LICENSE)
![Built with love](https://img.shields.io/badge/built%20with-%E2%9D%A4-FF8080.svg)

A text editor for me, written in C. 

![Screenshot of T editor's welcome message](/t.png)

T is a terminal text editor with less than 1K lines of code and no dependencies. It was built with the help of Snaptoken's booklet [Build Your Own Text Editor][snaptoken] which is based on [antirez's kilo][antirez].

## Usage

```bash
t <filename>
```

Keys:

```
CTRL-S: Save
CTRL-Q: Quit
CTRL-F: Find
	- ESC cancels search
	- Arrows navigate results
```

## Features

- Open, Save, Save As
- Incremental Search
- Syntax Highlighting(WIP)

## Roadmap

Core Functionality:

1. (Done) Project setup
1. (Done) Raw mode
1. (DONE) Input & output
1. (DONE) Text viewer
1. (DONE) Text editor
1. (DONE) Search
1. (20%) Syntax highlighting

Stretch Goals:

1. Custom Save-As
1. Custom Open file
1. Lua scripting
1. Multiple buffers

[snaptoken]: http://viewsourcecode.org/snaptoken/kilo/index.html
[antirez]: http://antirez.com/news/108

## License

- BSD 2-clause, see [LICENSE](/LICENSE) for more details.

