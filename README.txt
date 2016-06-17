//HOLES.C\\
The program has full utilization. File entry at the start (./holes INSERTFILENAME) is error checked
for both false file input or no input whatsoever (or extra arguments that aren't needed). All parts
of all fits worked perfectly for 3 different text files, each larger than the last. Basically, a for
statement was used for the entire chunk of working code, looped 4 times with each iteration changing
the program slightly to fit the "fit" of that part. Since holes don't come across as much with 
smaller files, the differences between the fits aren't terribly different, but they are present.

//PHILOSOPHERS.C\\
- Solving the philosopher's dining problem. Unfortunately, based on my knowledge of the problem, 
the results don't look terribly accurate. There are threads and semaphores used, and since I used a
different way about doing it at the start things changed and winded up as they are. It seems to 
work well until a certain number of philosophers are reached, where the program will repeat the same
thing for a while and then resume other functions. That being said, the program still uses threads,
semaphores and deals with it to a degree.

Usage is ./dine X Y where X is the number of philosophers (must be above 2, error checked) and Y is
the number of times they will eat (between 1 and 1000, also error checked).