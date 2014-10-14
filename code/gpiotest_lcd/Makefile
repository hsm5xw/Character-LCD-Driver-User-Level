# file: Makefile
# name: Hong Moon (hsm5xw@gmail.com)
# date: 2014-Sept

# compiler
CXX	= gcc

# .o files
OFILES	= driver.o mylcd.c simplegpio.c

# target name
TARGET	= testProgram

# suffix rule
.SUFFIXES: .o .c

# compile

main:	$(OFILES)
	$(CXX) -o $(TARGET) $(OFILES)

# clean up

clean:	
	/bin/rm -f *.o *~
	/bin/rm -f $(TARGET)

# dependencies (output of 'gcc -MM *.c')

driver.o: driver.c simplegpio.h mylcd.h
mylcd.o: mylcd.c mylcd.h simplegpio.h
simplegpio.o: simplegpio.c simplegpio.h

