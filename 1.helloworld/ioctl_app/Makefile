all: ioctl_test

ioctl_test: ioctl_test.c
	$(CROSS_COMPILE)gcc -o $@ $^

clean: 
	rm ioctl_test

deploy: ioctl_test
	scp $^ $(MY_DEPLOY_DIR)
