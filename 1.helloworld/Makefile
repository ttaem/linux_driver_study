obj-m += helloworld.o

all:
	echo $(PWD)
	make -C $(KERNEL_DIR) \
                M=$(PWD) modules

clean:
	make -C $(KERNEL_DIR) \
                M=$(PWD) clean

deploy:
	scp helloworld.ko $(MY_DEPLOY_DIR)
