# Operating Systems Midterm Project

This project consists of two major part:

- sum-of-even-digits
- system-calls-and-cpu-scheduling
- ticket-lock-and-readers-writers

## sum-of-even-digits
This is a small program written in c that uses **fork** and **pipe** system calls in linux.

It uses **fork** to create a child process and then uses **pipe** to create connection between these processes.

## system-calls-and-cpu-scheduling
This folder contains a copy of the xv6 operating system with some additional features described as below.

* Some new **system calls** are added to xv6.
* Some **cpu scheduling** algorithms are implemented for example round-robin with priority and etc.
* Some **user programs** are also written to test the previous parts.

## **ticket-lock-and-readers-writers**

This folder contains a copy of the xv6 operating system with some additional features described as below.

- A new lock called **ticket lock** is added.
- The famous **readers/writers** problem is implemented using this ticket lock.

## **exploring-linux**

In this folder there are some exercises in linux using python and c programming language to better understand this operating system.

