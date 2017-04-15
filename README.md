# T

A text editor for me, written in C. 

![Screenshot of T editor's welcome message](/t.png)

T is less than 1K lines of code and has no dependencies. It was built with the help of Snaptoken's booklet [Build Your Own Text Editor][snaptoken] which is based on [antirez's kilo][antirez].

# Usage

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

# Features

- Open, Save, Save As
- Incremental Search

# Roadmap

1. (Done) Project setup
1. (Done) Raw mode
1. (DONE) Input & output
1. (DONE) Text viewer
1. (DONE) Text editor
1. (DONE) Search
1. (0%) Syntax highlighting
1. Lua scripting

[snaptoken]: http://viewsourcecode.org/snaptoken/kilo/index.html
[antirez]: http://antirez.com/news/108

