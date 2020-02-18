bj-m +=my_timer.o

all:
        make -C /lib/modules/4.15.0-45-generic/build M=/usr/src/my_timer modules
clean:
        make -C /lib/modules/4.15.0-45-generic/build M=/usr/src/my_timer clean

