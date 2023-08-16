GCC = g++ -Wall -Werror -Wextra -std=c++17

.PHONY: clean SmartCalc tests

all: install check gcov_report

clean:
	rm -rf *.a && rm -rf *.o *.exe tests
	rm -rf *.info && rm -rf *.gcda && rm -rf *.gcno &&  rm -rf *.gcov *.html *.css *.cfg
	rm -rf report/ && rm -rf *.out
	rm -rf .clang-format SmartCalc/.clang-format manual

SmartCalc.a: clean
	$(GCC) -c SmartCalc/model/model.cc -o ./model.o
	$(GCC) -c SmartCalc/controller/controller.cc -o ./controller.o
	ar rcs SmartCalc_v2_0.a model.o controller.o
	ranlib SmartCalc_v2_0.a

tests: SmartCalc.a
	$(GCC) tests.cc -lgtest SmartCalc_v2_0.a -o tests
	./tests

gcov_report: SmartCalc.a
	$(GCC) --coverage tests.cc -lgtest SmartCalc/model/model.cc SmartCalc/controller/controller.cc -o tests
	./tests
	lcov --no-external -t "tests" -o tests.info -c -d .
	genhtml -o report tests.info
	rm *.gcda *.gcno

install:
	cd SmartCalc && cmake .
	cd SmartCalc && make
	mkdir ../build
	mv SmartCalc/SmartCalc.app ../build
	../build/SmartCalc.app/Contents/MacOS/SmartCalc

uninstall:
	cd SmartCalc && make clean
	rm -rf SmartCalc/CMakeFiles SmartCalc/CMakeCache.txt SmartCalc/Makefile
	rm -rf SmartCalc/librarys/CMakeFiles SmartCalc/cmake_install.cmake SmartCalc/librarys/CMakeCache.txt
	rm -rf SmartCalc/librarys/Makefile
	rm -rf SmartCalc/librarys/QCustomPlot-library/*.cmake SmartCalc/librarys/QCustomPlot-library/CMakeFiles
	rm -rf SmartCalc/librarys/QCustomPlot-library/Makefile
	rm -rf ../build

dist:
	cd ../ && tar -czf s21_SmartCalc_v2.0.tgz src

dvi_clean:
	rm -rf manual


dvi: dvi_clean
	makeinfo manual.texi --html
	open manual/index.html

check:
	cp ../materials/linters/.clang-format .clang-format
	cp ../materials/linters/.clang-format SmartCalc/.clang-format
	clang-format -n SmartCalc/*.cc
	clang-format -n SmartCalc/controller/*.cc SmartCalc/controller/*.h
	clang-format -n SmartCalc/model/*.cc SmartCalc/model/*.h
	clang-format -n SmartCalc/view/*.cc SmartCalc/view/*.h
	clang-format -n *.cc
	cppcheck --language=c++ *.cc
	cppcheck --language=c++ SmartCalc/*.cc
	cppcheck --language=c++ SmartCalc/model/*.cc
	cppcheck --language=c++ SmartCalc/model/*.h
	cppcheck --language=c++ SmartCalc/controller/*.cc
	cppcheck --language=c++ SmartCalc/controller/*.h
	cppcheck --language=c++ SmartCalc/view/*.cc
	cppcheck --language=c++ SmartCalc/view/*.h
	rm -rf .clang-format
	rm -rf SmartCalc/.clang-format
