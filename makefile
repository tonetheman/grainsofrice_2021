
all : junk test_maker

junk : mainline.cpp
	g++ -o junk mainline.cpp

test_maker : make_test_ppm.cpp
	g++ -o test_maker make_test_ppm.cpp
	
clean :
	rm -f ./junk


run :
	rm -f crud.ppm
	rm -f crud.png
	./junk

