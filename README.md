# 📚 README

## 🔌 Complete a shell program with "manual" handling of pipes

This program that collects messages from multiple programs and displays them on the screen. Use a named pipe for communication. 💡 **Hint:** Create an `rdfifo` program whose task is to create a FIFO queue and read data from it.

**❓ FAQ:**

| Question                                                                                                                        | Answer                                        |
|---------------------------------------------------------------------------------------------------------------------------------|-----------------------------------------------|
| How will you pass the common name of the FIFO queue to these programs?                                                          | Through a static variable                     |
| How to ensure that the program collecting messages works even when there is no program writing to the link?                     | Through an infinite loop process with `sleep` |
| How to ensure that messages from different programs are displayed in full, i.e., not separated by messages from other programs? | `flush`? (to be verified)                     |

### 📤 Output sample

```bash
[23:30:20](pid 17400) DEBUG: Passed rdfifo 73 - while1

karol@carlo:~/eclipse-workspaces/unx_sys_programming/Debug$ ./unx_sys_programming -w

Input option value=(null) set program to write to FIFO

[23:30:20](pid 17411) DEBUG: Passed wrfifo 148 : mkfifo exist: 17
[23:30:20](pid 17411) DEBUG: Passed wrfifo 157 - pipe opened to read-write
[23:30:20](pid 17400) DEBUG: Passed rdfifo 104 - Remove FIFO
[23:30:20](pid 17411) DEBUG: Passed wrfifo 174 : client succesed write to pipe: #0 test PID: 17411: text -> Thu Jan 28 23:36:02 2016
[23:30:20](pid 17400) DEBUG: Passed rdfifo 107 : reader reads record: #0 test PID: 17411: text -> Thu Jan 28 23:36:02 2016
[23:30:20](pid 17411) DEBUG: Passed wrfifo 174 : client succesed write to pipe: #1 test PID: 17411: text -> Thu Jan 28 23:36:03 2016
[23:30:20](pid 17400) DEBUG: Passed rdfifo 107 : reader reads record: #1 test PID: 17411: text -> Thu Jan 28 23:36:03 2016
[23:30:20](pid 17411) DEBUG: Passed wrfifo 174 : client succesed write to pipe: #2 test PID: 17411: text -> Thu Jan 28 23:36:04 2016
[23:30:20](pid 17400) DEBUG: Passed rdfifo 107 : reader reads record: #2 test PID: 17411: text -> Thu Jan 28 23:36:04 2016
[23:30:20](pid 17411) DEBUG: Passed wrfifo 174 : client succesed write to pipe: #3 test PID: 17411: text -> Thu Jan 28 23:36:05 2016
[23:30:20](pid 17400) DEBUG: Passed rdfifo 107 : reader reads record: #3 test PID: 17411: text -> Thu Jan 28 23:36:05 2016
[23:30:20](pid 17411) DEBUG: Passed wrfifo 174 : client succesed write to pipe: #4 test PID: 17411: text -> Thu Jan 28 23:36:06 2016
[23:30:20](pid 17400) DEBUG: Passed rdfifo 107 : reader reads record: #4 test PID: 17411: text -> Thu Jan 28 23:36:06 2016
[23:30:20](pid 17411) DEBUG: Passed wrfifo 174 : client succesed write to pipe: #5 test PID: 17411: text -> Thu Jan 28 23:36:07 2016
[23:30:20](pid 17400) DEBUG: Passed rdfifo 107 : reader reads record: #5 test PID: 17411: text -> Thu Jan 28 23:36:07 2016
[23:30:20](pid 17411) DEBUG: Passed wrfifo 174 : client succesed write to pipe: #6 test PID: 17411: text -> Thu Jan 28 23:36:08 2016
[23:30:20](pid 17400) DEBUG: Passed rdfifo 107 : reader reads record: #6 test PID: 17411: text -> Thu Jan 28 23:36:08 2016
[23:30:20](pid 17411) DEBUG: Passed wrfifo 174 : client succesed write to pipe: #7 test PID: 17411: text -> Thu Jan 28 23:36:09 2016
[23:30:20](pid 17400) DEBUG: Passed rdfifo 107 : reader reads record: #7 test PID: 17411: text -> Thu Jan 28 23:36:09 2016
[23:30:20](pid 17411) DEBUG: Passed wrfifo 174 : client succesed write to pipe: #8 test PID: 17411: text -> Thu Jan 28 23:36:10 2016
[23:30:20](pid 17400) DEBUG: Passed rdfifo 107 : reader reads record: #8 test PID: 17411: text -> Thu Jan 28 23:36:10 2016
[23:30:20](pid 17411) DEBUG: Passed wrfifo 174 : client succesed write to pipe: #9 test PID: 17411: text -> Thu Jan 28 23:36:11 2016
[23:30:20](pid 17400) DEBUG: Passed rdfifo 107 : reader reads record: #9 test PID: 17411: text -> Thu Jan 28 23:36:11 2016
[23:30:20](pid 17411) DEBUG: Passed wrfifo 180 - close fd
[23:30:20](pid 17400) DEBUG: Passed rdfifo 112 - EOF reader

[10]   Done                    ./unx_sys_programming -r

bash:~/eclipse-workspaces/unx_sys_programming/Debug$ ./unx_sys_programming -h

FIFO Program
A program without arguments creates a named pipe and writes data to it in a child process.
The program can be called with arguments so it works as read (r) from pipe or write to pipe (w).
A counter, PID and current time are written to the pipe.

Usage: ./unx_sys_programming [-r] [-w]
```

## 🚀 Usage example

**Basic usage:**

```bash
./unx_sys_programming
```

**Or use with multiple processes:**

```bash
./unx_sys_programming -r
./unx_sys_programming -w
./unx_sys_programming -w
./unx_sys_programming -w
```

# 🔀 Fork read environment - Tasks

## Task Definitions

- **z1:** 📝 Write a program that shows which attributes of the parent process are inherited by the child process started with the `fork()` function, and which receive new values.

- **z2:** 📝 Write a program that shows which process attributes are preserved after the `exec()` function is executed.

- **z3:** 📝 Write a program that displays the process identifier (PID) and the name of the associated command for all processes started by the user specified in the program's call line.

💡 **Hint:** This information can be obtained by browsing the `/proc` directory from files (we are interested in directories whose owner is the given user) and the `/proc/PID/status` files

## 📋 Process Attributes

Each process is characterized by certain attributes:

| Attribute          | Description                                    |
|--------------------|------------------------------------------------|
| 🆔 PID              | Process identifier                             |
| 👨‍👩‍👧 PPID             | Parent process identifier                      |
| 👤 Real UID         | Real user identifier of the process owner      |
| 👥 Real GID         | Real process group identifier                  |
| ⚡ Effective UID    | Effective user identifier of the process owner |
| ⚡ Effective GID    | Effective process group identifier             |
| 📂 Directories      | Current directory and root directory           |
| 🔐 File mask        | File creation mask                             |
| 🔌 Session ID       | Session identifier                             |
| 💻 Terminal         | Controlling terminal                           |
| 📁 File descriptors | Descriptors of open files                      |
| 📢 Signal handling  | Signal handling settings                       |
| 🌍 Environment      | Environment variable settings                  |
| 💾 Resources        | Resource limits

## 🧬 Process Inheritance & Differences

### Inherited Properties

The child process inherits many properties from the parent process:

- Real user identifier, real group identifier
- Effective user identifier, effective group identifier
- Additional group identifiers
- Session identifier, controlling terminal
- User ID set signal and group ID set signal
- Open file descriptors (they are copied)
- Current working directory, root directory
- File creation mask, signal mask and signal handling dispositions
- Close-on-exec flag for all open file descriptors
- Environment, attached shared memory segments
- System resource limits

### Key Differences

However, there are certain differences between the parent and child processes:

1. **Return value** from `fork()` - different in parent vs child
2. **Process identifiers** - each process gets a unique PID
3. **Parent process identifiers** - in the child process this is the parent's PID; in the parent process the PPID doesn't change
4. **Timing values** - in the child process, `tms_utime`, `tms_cutime` and `tms_ustime` are equal to 0
5. **File locks** - the child does not inherit file locks established in the parent process
6. **Pending alarms** - in the child process, all pending alarms are zeroed
7. **Pending signals** - in the child process, the set of pending signals is zeroed
