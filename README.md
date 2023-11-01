# ush
Modular and FAST shell (package manager included) for Linux Distros in C++

# What is this "modular"? <br>
You can EXTEND core-ush by adding binaries, or by changing bindir to /bin and having access to all your programs installed on your base linux system.
<br>
# How to install? <br>
So far, this is ONLY installable on linux operating systems. No I will NOT be making any binaries for macOS or Windows.

## Installation Steps<br>
### Downloading Binaries Directly

Step 1: Download the binaries from the `releases` section.<br>
Step 2: Run `./shell` in your terminal and run `tutorial` to get a brief tutorial on ush.<br>

### Compiling with G++

Step 1: Download source files<br>
Step 2: Download lib readline (You can use google).<br>
Step 3: Run command in terminal `g++ -o ./shell ./shell.cpp -lreadline` to compile shell.cpp<br>
Step 4: Run `./shell` in your terminal and run `tutorial` to get a brief tutorial on ush.<br>

## What is ush?<br>
uSH is a fast shell (particularly since it's made in C++, known for it's speed) which is modular (supports external binaries) and has a default package manager (ups) installed which has *yet* 1 total package but that is to change soon! 
