
build:
	clear
	gcc main.c -o main  -Wall -Werror -std=gnu11 -lm -O2 -g3

buildsan:
	gcc main.c -o main  -Wall -Werror -std=gnu11 -lm -O2 -g3
	
test TEST: 
	just build
	./main < Tests/archivio_test_aperti/open_{{TEST}}.txt 

testSave TEST:	
	just build
	./main < Tests/archivio_test_aperti/open_{{TEST}}.txt > Tests/archivio_test_aperti/open_{{TEST}}.out


diff TEST:
	just build
	./main < Tests/archivio_test_aperti/open_{{TEST}}.txt > Tests/archivio_test_aperti/open_{{TEST}}.out
	-colordiff --suppress-common-lines  <(nl Tests/archivio_test_aperti/open_{{TEST}}.out) <(nl Tests/archivio_test_aperti/open_{{TEST}}.output.txt)

diffLine TEST LINE: 
	just build
	head -n {{LINE}} Tests/archivio_test_aperti/open_{{TEST}}.txt > test.in
	head -n {{LINE}} Tests/archivio_test_aperti/open_{{TEST}}.output.txt > test.output.txt
	./main < test.in > test.out
	-colordiff --suppress-common-lines -y <(nl test.out) <(nl test.output.txt)

debug TEST:
	just build
	gdb -ex "run < Tests/archivio_test_aperti/open_{{TEST}}.txt" ./main

debugLine TEST LINE:
	just build
	head -n {{LINE}} Tests/archivio_test_aperti/open_{{TEST}}.txt > test.in
	gdb -ex "run < test.in" ./main

diffUntil TEST:
	for ((i=1; i<={{TEST}}; i++)); do just diff $i; read -p"✅ Press enter to ontinue. "; done

diffFromUntil TESTA TESTB:
	for ((i={{TESTA}}; i<={{TESTB}}; i++)); do just diff $i; read -p"✅ Press enter to ontinue. "; done

time TEST:
	time just testSave {{TEST}}