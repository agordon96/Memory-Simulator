//HOLES.C\\
The program has full utilization. File entry at the start (./holes INSERTFILENAME) is error checked
for both false file input or no input whatsoever (or extra arguments that aren't needed). All parts
of all fits worked perfectly for 3 different text files, each larger than the last. Basically, a for
statement was used for the entire chunk of working code, looped 4 times with each iteration changing
the program slightly to fit the "fit" of that part. Since holes don't come across as much with 
smaller files, the differences between the fits aren't terribly different, but they are present.

Format for input files are <Letter> <size of memory> for every line of code. The memory is set by
default at 128 units, but can be increased if you edit "define MEM 128" at the top of the source code.
