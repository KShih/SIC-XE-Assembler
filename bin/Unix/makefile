# the simple SIC/XE Assembler 

# this must use GNU Make ("make" on Linux and Mac OS X, "gmake" on Solaris)
# compiler options and libraries for Linux, Mac OS X or Solaris

# compiler options -- C99 with warnings
OPT_GCC = -std=c99 -Wall -Wextra

ifeq ($(OSTYPE),linux)
  OPT = -D_XOPEN_SOURCE=700
  LIB = -lrt
endif
ifeq ($(OSTYPE),darwin)    # Mac OS X
  OPT = 
  LIB = 
endif
ifeq ($(OSTYPE),solaris)
  OPT = -D_XOPEN_SOURCE=600
  LIB = -lrt
endif

# Copy Input File to directory
#CopyInput:
#	cp ../../input/FIN-codetest_2017.txt .
#	cp ../../input/FIN-errorcode_2016.txt .

# Copy src File to directory
#CopySrc: 
#	cp ../../src/generate_Format.cpp .
#	cp ../../src/generate_Locaddr.cpp .
#	cp ../../src/generate_Objcode.cpp .
#	cp ../../src/generate_Output.cpp .

all: generate_Format generate_Locaddr generate_Objcode generate_Output
Format: generate_Format.cpp
	gcc $(OPT_GCC) $(OPT) -o generate_Format generate_Format.cpp $(LIB)

LocAddr: generate_Locaddr.cpp
	gcc $(OPT_GCC) $(OPT) -o generate_Locaddr generate_Locaddr.cpp $(LIB)

Objcode: generate_Objcode.cpp
	gcc $(OPT_GCC) $(OPT) -o generate_Objcode generate_Objcode.cpp $(LIB)

Output: generate_Output.cpp
	gcc $(OPT_GCC) $(OPT) -o generate_Output generate_Output.cpp $(LIB)

#run: format.txt Loc_addr.txt PRGRAM_BLOCKS.txt SYMTAB.txt OBJECT_CODE.txt Output.txt
run: generate_Format generate_Locaddr generate_Objcode generate_Output
	./generate_Format
	./generate_Locaddr
	./generate_Objcode
	./generate_Output

clean:
	rm -f generate_Format generate_Locaddr generate_Objcode generate_Output format.txt Loc_addr.txt PRGRAM_BLOCKS.txt SYMTAB.txt OBJECT_CODE.txt Output.txt 

