#----------------------------------------------------------------------
# Makefile for CS415/515 Assignment 1
#----------------------------------------------------------------------

CFLAGS = -std=c99 -pthread -g queue.c
CC = gcc

JFLAGS = -g
JC = javac

.PRECIOUS: %.c %.java

.c.o:
	$(CC) $(CFLAGS) $*.c

.java.class:
	$(JC) $(JFLAGS) $*.java

