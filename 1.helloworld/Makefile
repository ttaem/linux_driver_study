obj-m += helloworld.o helloworld_char_driver.o helloworld_char_driver_class.o

all:
	echo $(PWD)
	make -C $(KERNEL_DIR) \
                M=$(PWD) modules

clean:
	make -C $(KERNEL_DIR) \
                M=$(PWD) clean

deploy:
	scp helloworld.ko helloworld_char_driver.ko helloworld_char_driver_class.ko $(MY_DEPLOY_DIR)
