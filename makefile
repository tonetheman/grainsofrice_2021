
junk : mainline.cpp
	g++ -o junk mainline.cpp

clean :
	rm -f ./junk


run :
	rm -f crud.ppm
	rm -f crud.png
	./junk

