# OSProject1ProducerConsumer

Kevin Coran Operating Systems Project 1

The goal for this assignment is to implement a producer/consumer problem in linux using shared memory and semaphores.\
The program will produce and consume items to/from a table with a maximum of 2 items.\
If the table is full or currently being acted on, then the producer will not act.\
If the table is empty or currently being acted on, then the consumer will not act.\
The code is compiled and run by the following commands:\
$gcc producer.c -pthread -lrt -o producer\
$gcc consumer.c -pthread -lrt -o consumer\
$./producer & ./consumer &

Example Output:

![image](https://user-images.githubusercontent.com/73201894/139344993-ac342c65-4073-4070-94c4-299a956c0d86.png)



The first obstacle was setting up a programming environment. I used virtualbox to virtualize an ubuntu environment.\
I used visual studio code to edit the code and compiled with gcc through the terminal.

In the actual program, the first difficulty was creating the shared memory and the semaphores.\
Once they were created then I had to implement the logic of the producer/consumer problem\
This was done by looping and essentially waiting when the other is in use or full/empty.
