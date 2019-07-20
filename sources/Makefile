
CPLEXDIR      = ./cplex-12.7.1/cplex
CONCERTDIR    = ./cplex-12.7.1/concert

SYSTEM     = x86-64_linux
LIBFORMAT  = static_pic

CCOPT = -g -w -m64 -O -fno-strict-aliasing -fexceptions -DNDEBUG -DIL_STD -Wno-ignored-attributes

# ---------------------------------------------------------------------
# Link options and libraries
# ---------------------------------------------------------------------

CPLEXBINDIR   = $(CPLEXDIR)/bin/$(BINDIST)
CPLEXLIBDIR   = $(CPLEXDIR)/lib/$(SYSTEM)/$(LIBFORMAT)
CONCERTLIBDIR = $(CONCERTDIR)/lib/$(SYSTEM)/$(LIBFORMAT)

CCLNDIRS  = -L$(CPLEXLIBDIR) -L$(CONCERTLIBDIR)


CONCERTINCDIR = $(CONCERTDIR)/include
CPLEXINCDIR   = $(CPLEXDIR)/include

CCLNFLAGS = -lconcert -lilocplex -lcplex -lm -lpthread

CCFLAGS = $(CCOPT) -I$(CPLEXINCDIR) -I$(CONCERTINCDIR)



all: exec

main.o: main.cpp Data.h PresentationSimple.h MyChecker.h
	g++ -c main.cpp -o main.o

Data.o: Data.cpp  Data.h
	g++ -c Data.cpp

MyChecker.o: MyChecker.cpp  MyChecker.h
		g++ -c MyChecker.cpp

PresentationSimple.o: PresentationSimple.cpp PresentationSimple.h
	g++ -c PresentationSimple.cpp

PresentationExacte.o : PresentationExacte.cpp PresentationExacte.h
	g++ -c $(CCFLAGS) $(CCLNDIRS)  PresentationExacte.cpp -o PresentationExacte.o

exec: main.o Data.o PresentationSimple.o MyChecker.o PresentationExacte.o
	g++ $(CCFLAGS) $(CCLNDIRS)  main.o Data.o PresentationSimple.o MyChecker.o PresentationExacte.o $(CCLNFLAGS) -o exec

clean:
	rm Checker
	rm -f *.o
	rm -rf *~
