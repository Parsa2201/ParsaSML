# ParsaSML
The SML language I've written using C

First you should tell the program how many lines do you need.
the lines, save the instructions and the variables.

Then you can write your code.
after your code is finished, type: "END".
It'll be executing your code.
after it is finished, you can press "S" for Stop, "E" for Execution, and "P" for Program (write a new code).

Syntax:
Every line has to parts, one for the command, and one for the line-number.

Commands:

"READ" : get an int from the user and save it in the line-number.
ex: "READ 50" means get a number and save it in the line 50.

"WRITE" : show the value of line-number
ex: "WRITE 50" means show the value of line 50.

"LOAD" : save value of the line-number into accumulator.
ex: "LOAD 50" means set the value of accumulator to value of line 50.

"STORE" : save value of the accumulator into the line-number.
ex: "STORE 50" means set the value of line 50 to value of accumulator.

"ADD" :
ex: 

"Subtract" :
ex:

"DIVIDE" : 
ex: 

"MULTIPLY" : 
ex:

"BRANCH" : go to the line-number and continue reading from that position,
ex: "BRANCH 3" means go to line 3.

"BRANCHNEG" : got to line-number (if the value of accumulator is negative).
ex: "BRANCHNEG 3" means if accumulator is less than zero, go to line 3.

"BRANCHZERO" : 
ex:

"BRANCHPOS" : 
ex:

"HALT" : end the program
