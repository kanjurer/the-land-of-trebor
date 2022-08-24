#config
COMPILER = gcc
CSTD     = --std=c18
INCLUDES = -Ilib
LIBFLAGS = -lm -lpthread


#files
OBJECT_FILES = simulation.o heroes.o locations.o
LIBRARY_OBJECT_FILES = array_list.o heap.o linked_list.o queue.o
OUTPUT_FILES = level_alive level_dead power_alive power_dead subtlety_alive subtlety_dead strategy_alive strategy_dead charm_alive charm_dead

#main executable
simulation: $(OBJECT_FILES) $(LIBRARY_OBJECT_FILES)
	$(COMPILER) $(CSTD) $(INCLUDES) $(LIBFLAGS) $(OBJECT_FILES) $(LIBRARY_OBJECT_FILES) -o deusex


#object files
heroes.o: heroes.c heroes.h 
	$(COMPILER) $(CSTD) $(INCLUDES) $(LIBFLAGS) -c heroes.c -o heroes.o

locations.o: locations.c locations.h 
	$(COMPILER) $(CSTD) $(INCLUDES) $(LIBFLAGS) -c locations.c -o locations.o

simulation.o: simulation.c simulation.h 
	$(COMPILER) $(CSTD) $(INCLUDES) $(LIBFLAGS) -c simulation.c -o simulation.o


#libraries
array_list.o: lib/array_list.c lib/array_list.h
	$(COMPILER) $(CSTD) $(INCLUDES) $(LIBFLAGS) -c lib/array_list.c -o array_list.o

heap.o: lib/heap.c lib/heap.h
	$(COMPILER) $(CSTD) $(INCLUDES) $(LIBFLAGS) -c lib/heap.c -o heap.o

queue.o: lib/queue.c lib/queue.h
	$(COMPILER) $(CSTD) $(INCLUDES) $(LIBFLAGS) -c lib/queue.c -o queue.o

linked_list.o: lib/linked_list.c lib/linked_list.h
	$(COMPILER) $(CSTD) $(INCLUDES) $(LIBFLAGS) -c lib/linked_list.c -o linked_list.o


#clean
clean:
	rm -f $(OBJECT_FILES) $(LIBRARY_OBJECT_FILES) $(OUTPUT_FILES) deusex

