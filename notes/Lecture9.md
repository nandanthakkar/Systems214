## Systems Programming - Lecture 9

#### File Permissions
Read:
Write: 
Execute


(Side Node: <b>touch</b>: goes to a file and updates the file to update the date to right now. If the file doesn't exist, it will be created)

#### Changing File Permissions & Owners

##### chown
`chown`: Change Owner

##### chmod
`chmod`: Change mode

`chmod a+r <filename>` - For all user, add the read permission.
`chmod a-r <filename>` - Remove read permission for everybody, including yourself.
`chmod u+r <filename>` - Giving back the ability for me to read a file.

different levels of organization a file can undergo:
a: all
o: owner
u: user
g: group

(rwx)(rwx)(rwx)
first tuple: user
second tuple: group
third tuple: Specifies the owner

reads the permissions from left to right. It first starts off by reading if the user running either `chmod` or `chown` is a user. If so, the it allows the command to run. If you are not user, it will check what group you are in and see if you have permissions to run it. Finally, if you are not in an applicaable group, it then finally checks to see if you are the owner. This, unix machines will compare see if you can edit the permission so of file from the least general permissions to the most specific.

---

#### Killing a Process

- `^c` is the eaiest way to kill a command, but what if the command is not in the foreground. `^z` will make a command go from the foreground to the background. 
- The `kill` command will try to run and turn off a process. Some processes run at such a high level that you can't just kill them without sudo and or a more powerful kill command. `kill -9 <pid>` will force shut down a command. `kill - KILL` is another way to force kill a process. 
- `ps` will show a current snap shot of the current programs that you are running
- `ps aux` shows all the commands all users are running.
- `ps aux | less` runs `ps aux`, but shows less of the output. Similarly, you can use `ps aux | more` 
- `top` shows everything that is running on the machine. It can show you info such as: how many users are running, the CPU ussage, etc.
- `top 1` shows the percentage of CPU usage on the machine. Gives you a sense of how many CPUs you are using as well as the proces id.

---

`ln` a link. It a link is a poi

