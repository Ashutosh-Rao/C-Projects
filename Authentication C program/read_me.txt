my_pwck verifies the integrity of the users and authentication information. It checks that all entries in /etc/passwd and /etc/shadow have the proper format and contain valid data.

Checks are made to verify that each entry has:

       *   the correct number of fields
       *   passwd entries are unique in passwd file
       *   a unique and valid user name
       *   a valid user and group identifier
       *   a valid home directory

shadow checks are enabled when a second file parameter is specified or when /etc/shadow exists on the system. These checks are the following:

       *   every passwd entry has a matching shadow entry, and every shadow entry has a matching passwd entry
       *   shadow entries have the correct number of fields
       *   shadow entries are unique in shadow

If the above checks fails, the user will be informed.

By default, this tool operates on the files /etc/passwd and /etc/shadow. The user may select alternate files with by sending them as command level arguments to this tool. 

Note:- As this tool cannot access directly on /etc/passwd and /etc/shadow files, due to non availablity of super user or admin acecss, I have used dummy passwd and
shadw files for testing. There are multiple dirs that contains different test scenarios


//Contents//
_______________

the pswc_assignment folder contains the following:
 
>obj  
>src  
>testing
>read_me.txt 

***obj directory***

The obj directory contains the object files and the executable that is compiled on my system (Ubuntu 16.04 LTS) on virtual box.
The name of the exectable is my_pwck .
Thus, to run the program, the user must go to the testing directory and the user needs to enter ../../obj/my_pwck


***src directory***

This contains the .c , .h and make files.

my_pwck.c  : contains the main routines for this tool 
paswd.c    : contains the routines related to the password file content checks
shadw.c    : contains the routines related to the shadow file content checks
grp.c      : contains the routines related to the group file content checks
def.h      : contains all the definitions for the data structures used
Makefile   : this is the makefile

***testing directory***

This directory contains various test scenario under each sub directory:
check           : general testing scenario
dup_passwd      : this is the test scenario for the duplicate password entry
group_const     : this is the test scenario for checking group consistancy within the file
passwd_shadow   : this is the test scenario for checking thr consistancy across both password and shadow files
user_grp        : this is the test scenario for checking the group ID  
dup_group       : this is the test scenario for the duplicate group entry
dup_shadow      : this is the test scenario for the duplicate shadow entry
passwd_const    : this is the test scenario for checking password consistancy within the file
shadow_const    : this is the test scenario for checking shadow consistancy within the file

