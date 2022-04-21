CXX = g++
CXXFLAGS = -g

CCR = riscv64-unknown-elf-g++
LINKR = riscv64-unknown-elf-g++

CCRFLAGS = -static -fno-common -fno-builtin-printf -fno-use-cxa-atexit -specs=htif_nano.specs -O3 -I./
LINKRFLAGS = -static -specs=htif_nano.specs -O3

EXEC = main
EXECR = mainrisc

OBJS =  atom.o ForceFunction.o main.o neighbor.o 
OBJR =  atom.riscv.o ForceFunction.riscv.o main.riscv.o neighbor.riscv.o
INC = atom.h comm.h force.h force_lj.h ljs.h neighbor.h openmp.h threadData.h timer.h types.h

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)
	@if [ ! -d Compile ]; then mkdir Compile; fi
	@mv $(OBJS) Compile;

$(EXECR): $(OBJR)
	$(CCR) $(CCRFLAGS) -o $(EXECR).riscv $(OBJS)
	$(MAKE) -f makefile link

atom.o: atom.cpp
	${CXX} ${CXXFLAGS} -c atom.cpp

ForceFunction.o: ForceFunction.cpp
	${CXX} ${CXXFLAGS} -c ForceFunction.cpp

neighbor.o: neighbor.cpp
	${CXX} ${CXXFLAGS} -c neighbor.cpp

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c main.cpp

atom.riscv.o: atom.cpp
	${CCR} ${CCRFLAGS} -c atom.cpp

ForceFunction.riscv.o: ForceFunction.cpp
	${CCR} ${CCRFLAGS} -c ForceFunction.cpp

main.riscv.o: main.cpp
	${CCR} ${CCRFLAGS} -c main.cpp
	
neighbor.riscv.o: neighbor.cpp
	${CCR} ${CCRFLAGS} -c neighbor.cpp



link: $(OBJS)
	$(LINKR) $(LINKRFLAGS) $(OBJS) -o $(EXECR).riscv 
	@if [ ! -d CompileRISCV ]; then mkdir CompileRISCV; fi
	@mv $(OBJS) CompileRISCV;

$(OBJS): $(INC)

clean:
	rm -f -r Compile CompileRISCV main mainrisc.riscv *.o