# Lab 2
[Fork](https://docs.github.com/en/get-started/quickstart/fork-a-repo) this repo and clone it to your machine to get started!

## Team Members
- team member 1: Kaelyn Cho
- team member 2: Jeremy Pogue

## Lab Question Answers

Question 1: How did the reliability of UDP change when you added 50% loss to your local
environment? Why did this occur?

The text entered on one terminal had a 50% chance of appearing on the otheer terminal, but if it was going to appear it did almost immediately.


Question 2: How did the reliability of TCP change? Why did this occur?

There was sometimes latency and large chunks of input would appear from one terminal to another after an extended period of time. All the text would eventually appear, but I couldn't predict when.


Question 3: How did the speed of the TCP response change? Why might this happen?

TCP became on average MUCH slower with loss, but it didn't lose any data. This is because TCP has "slow start", so that when there is packet loss the system resends the data (it keeps a record of all the data sent to track whether it needs to be resent or not). It is a function called "Selective Repeat".

cite: https://www.isi.edu/nsnam/DIRECTED_RESEARCH/DR_HYUNAH/D-Research/slow-start-tcp.html

...
