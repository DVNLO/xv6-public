# UCR CS 202 Lab 2 Kernel Threads
## How to play frisbee
I implemented two frisbee programs `frisbee_lock` and `frisbee_semaphore`. Both programs are runnable from the xv6 command line as follows:

```
$ frisbee_lock [player count] [pass count]
```
```
$ frisbee_semaphore [player count] [pass count]
```
For example, to play a game of frisbee with 4 players and 8 passes using the locking implementation run the following, 
```
$ frisbee_lock 4 8
```
