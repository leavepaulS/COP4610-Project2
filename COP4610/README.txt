# -------------------------- #
# COP4610           Project2 #

# - GROUP MEMBERS - #

 - Paul Santora
 - Jared Usher
 - Hengwei Xing


# - FILE LISTING - #

 - Part 1
    - empty.c
    - empty.trace
    - part1.c
    - part1.trace

 - Part 2
    - my_timer.c
    - Makefile

 - Part 3
    - elevator.c
    - Makefile

 - README.txt


# - Tar File Name - #
    project2_Santora_Usher_Xing.tar


# - MAKEFILE DESCRIPTION - #

 - Part 2 and Part 3
   creates *.ko files to be installed as kernel modules

To Compile

 - Part 2
   > sudo make
   > sudo insmod my_timer.ko

To remove *.o, *.ko, shell targets and files created by Makefile
   make clean

 - Part 3
   elevator.c and Makefile should be in directory usr/src/elevator
   producer.c, consumer.c, wrappers.h and provided Makefile are not in
   usr/src/elevator

   in usr/src/elevator
   > sudo make

   for producer.c, consumer.c, wrappers.h and provided Makefile
   > sudo make
   > sudo make insert
   > sudo insmod elevator.ko
   
To remove *.o, *.ko, shell targets and files created by Makefile
   make remove


# - DIVISION OF LABOR - #

Hengwei Xing
 - Part 3
   System Call Functions

Jared Usher
 - Part 3
   Kernel Module setup
    
Paul Santora
 - Part 3
   Kernal Module proc file formating

Everyone
 - Part 1
 - Part 2
 - Part 3

We worked almost exclusively together for the project


# - KNOWN ISSUES / UNFINISHED SECTIONS- #

 - Part 3 is incomplete

   The Module and all related files can be compiled together
 with the Makefile provided to us, and we can load and unload
 the module with no issues. However, our scheduler is incomplete
 and does not accepted requests and service passengers.

 - Part 3 cat proc/elevator
   
   At top of proc/elevator, there is a line of random characters
 that appears most likely because of kmalloc. Does not affect anything.


# - GIT COMMIT LOG - #

 Screen shots uploaded to canvas