all: test_code

clean: test_code_clean

.PHONY: test_code
test_code:
	make -C app/dw1000/decadriver
	make -C app/dw1000/hal
	make -C app/util_app

.PHONY: test_code_clean
test_code_clean:
	make -C app/dw1000/decadriver clean
	make -C app/dw1000/hal clean
	make -C app/util_app clean
