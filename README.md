# Notes
```
< infile grep a1 | wc -w > outfile
```
### < 
Input redirection. 

Redirects the content of infile to the standard input 
so that when grep is reading from the standard input, it gets the content of infile).
### |
Redirects the output of the command on the left to the input of the command on the right.
### >
Output redirection (writes the output of the wc command into the outfile).
### >>
The >> symbol does almost the same thing as the > symbol.

The > symbol replaces the content of the file on the right with the output of the command on the left.


The >> symbol appends the output of the command on the left at the end of the file.
### <<
The << symbol is an input "redirection" symbol.


It makes the shell read from the standard input until it encounters only a specific LIMITER on the stdin. 


Example: cmd << LIMITER | cmd1 >> file

## Functions used
```
int access(const char *pathname, int mode);
```
access() checks whether the program can access the file pathname. 
```
int dup2(int oldfd, int newfd);
```
dup2() makes newfd be the copy of oldfd, closing newfd first if necessary.
```
int pipe(int pipefd[2]);
```
```
pid_t fork(void);
```
When you call fork(), the operating system creates a new process that is a copy of the calling process.
```
pid_t waitpid(pid_t pid, int *status, int options);
```
```
int execve(const char *filename, char *const argv[], char *const envp[]);
```
```
int unlink(const char *pathname);
```
