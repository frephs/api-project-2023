MAKEFLAGS += -s

# Basic build rule
build:
	$(CC) main.c -o main -Wall -Werror -std=gnu11 -lm -O2 -g3

# Build with sanitizer (same as build for now)
buildsan:
	$(CC) main.c -o main -Wall -Werror -std=gnu11 -lm -O2 -g3

# Run test with input file based on TEST variable
test:
	$(MAKE) build
	./main < Tests/archivio_test_aperti/open_$(TEST).txt

# Run test and save output to file based on TEST variable
testSave:
	$(MAKE) build
	./main < Tests/archivio_test_aperti/open_$(TEST).txt > Tests/archivio_test_aperti/open_$(TEST).out

# Diff test output against expected output and show colored diff if failed
diff:
	$(MAKE) build
	./main < Tests/archivio_test_aperti/open_$(TEST).txt > Tests/archivio_test_aperti/open_$(TEST).out

	@if diff -q Tests/archivio_test_aperti/open_$(TEST).out Tests/archivio_test_aperti/open_$(TEST).output.txt; then \
		echo "✅ Test $(TEST) passed"; \
	else \
		echo "❌ Test $(TEST) failed"; \
		colordiff --suppress-common-lines Tests/archivio_test_aperti/open_$(TEST).out Tests/archivio_test_aperti/open_$(TEST).output.txt; \
	fi

# Diff specific lines in a test file and output file
diffLine:
	$(MAKE) build
	head -n $(LINE) Tests/archivio_test_aperti/open_$(TEST).txt > test.in
	head -n $(LINE) Tests/archivio_test_aperti/open_$(TEST).output.txt > test.output.txt
	./main < test.in > test.out
	colordiff --suppress-common-lines -y <(nl test.out) <(nl test.output.txt)

# Debug a test using gdb
debug:
	$(MAKE) build
	gdb -ex "run < Tests/archivio_test_aperti/open_$(TEST).txt" ./main

# Debug specific lines using gdb
debugLine:
	$(MAKE) build
	head -n $(LINE) Tests/archivio_test_aperti/open_$(TEST).txt > test.in
	gdb -ex "run < test.in" ./main

# Run diff on multiple tests until a specified number
diffUntil:
	$(MAKE) build
	for i in $(shell seq 1 $(TEST)); do $(MAKE) diff TEST=$$i; done

# Run diff from one test to another
diffFromUntil:
	$(MAKE) build
	for i in $(shell seq $(TESTA) $(TESTB)); do $(MAKE) diff TEST=$$i; done

# Measure the time of running a test and saving the output
time:
	time $(MAKE) testSave TEST=$(TEST)
