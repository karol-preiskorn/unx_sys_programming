/**
 * Uzupełnij program shell z o „ręczną” obsługę potoków.
 * ----------------------------------------------------
 * Napisz program, który zbiera komunikaty od wielu programów i wyświetla je na ekranie. Do komunikacji użyj potoku nazwanego.
 *
 * Wskazówka: Utwórz program rdfifo, którego zadaniem jest utworzenie kolejki FIFO i czytanie z niej danych.
 * Utwórz program wrfifo, który otwiera kolejkę FIFO tylko do zapisu i wpisuje do niej dane (np. swoj pid i czas).
 *
 * W jaki sposób przekażesz wspólną nazwę kolejki FIFO do tych programów?
 * W jaki sposób zapewnić działanie programu zbierającego komunikaty również wtedy, kiedy nie ma programu piszącego do łącza?
 * Jak zapewnić to, że komunikaty pochodzące od różnych programów wyświetlane są w całości, tzn. nie są rozdzielane  komunikatami od innych programów?
 */
#define DEBUG_MODE

#ifdef DEBUG_MODE
#define logs(...) printf("[%s](pid %d) DEBUG: Passed %s %d - %s\n", __TIME__, (int) getpid(), __FUNCTION__, __LINE__, ##__VA_ARGS__);
#define logs_d(...) printf("[%s](pid %d) DEBUG: Passed %s %d - %s : %d\n", __TIME__, (int) getpid(), __FUNCTION__, __LINE__, ##__VA_ARGS__);
#else
#define logs(...)
#endif

#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFOARG 1
#define PIPE_BUF 100
#define FIFO_PERMS (S_IRWXU | S_IWGRP| S_IWOTH)
#define FIFO "temp.fifo"

#define BUFFERSIZE 500000
char buf[BUFFERSIZE]; // read buf

char* mygettime() {
	time_t mytime;
	mytime = time(NULL);
	return (ctime(&mytime));
}

/**
 * Serwer named pipe
 * -----------------
 * @param argc
 * @param argv
 * @return
 */
int rdfifo() {

	int fd;
	int read_buf;
	int fifo, var;

	/* There are *two* ways the open can fail: the pipe doesn't exist
	 * yet, *or* it succeeded, but a different writer already opened
	 * it but didn't yet remove it.
	 */
	while (1) {
		while ((fifo = open(FIFO, O_RDONLY)) == -1) {
			/* Since you didn't specify O_CREAT in the call to open, there
			 * is no way that namedpipe4 would have been created by the
			 * reader.  If there *is* now a namedpipe4, a remove here
			 * would delete the one the writer created!
			 */
			sleep(1);
		}

		/* Get an exclusive lock on the file, failing if we can't get
		 * it immediately.  Only one reader will succeed.
		 */
		if (flock(fifo, LOCK_EX | LOCK_NB) == 0)
			break;

		/* We lost the race to another reader.  Give up and wait for
		 * the next writer.
		 */
		close(fifo);
	}
	/* We are definitely the only reader.
	 */

	/* *Here* we delete the pipe, now that we've locked it and thus
	 * know that we "own" the pipe.  If we delete before locking,
	 * there's a race where after we opened the pipe, a different
	 * reader also opened, deleted, and locked the file, and a new
	 * writer created a new pipe; in that case, we'd be deleting the
	 * wrong pipe.
	 */
	remove(FIFO);

	while ((var = read(fifo, buf, BUFFERSIZE)) > 0) {
		logs_d("Reader reads  record:", buf);
		/* No need to sleep; we'll consume input as it becomes
		 * available.
		 */
	}

	close(fifo);
	logs("EOF..\n");
	exit(0);

}

/**
 * Klient named pipe
 *
 * write to pipe
 *
 * @param argc
 * @param argv
 * @return
 */
int wrfifo() {
	time_t curtime;
	int len;
	char buf[PIPE_BUF];
	int fd;

	if ((unlink(FIFO)) == -1) {
		logs("Error unlink FIFO")
	} else {
		logs("unlink fifo");
	}

	if ((mkfifo(FIFO, FIFO_PERMS) == -1) && (errno != EEXIST)) {
		logs("Server failed to create a FIFO");
		return (1);
	} else {
		logs("create FIFO - mkfifo(FIFO, FIFO_PERMS)");
	}

	logs("start");
	if ((fd = open(FIFO, O_WRONLY)) == -1) {
		logs("Client failed to open log fifo for writing");
		return (1);
	} else {
		logs("pipe opened to write");
	}
	curtime = time(NULL);

	printf("PID: %d: text -> %s", (int) getpid(), ctime(&curtime));
	len = strlen(buf);
	if (write(fd, buf, len) != len) {
		logs("Client failed to write");
		return (1);
	} else
		logs("client succesed write to pipe ");
	logs("close");
	close(fd);
	return (0);
}

/**
 * main
 *
 * @return
 */
int main(int argc, char *argv[]) {
	pid_t pid;
	int i;

	logs("start program");

	pid = fork();
	/* proces potomny */
	if (pid == (pid_t) 0) { /* brak obsługi błędów */
		/**
		 * Odczytywanie
		 */
		for (i = 0; i < 3; i++) {
			rdfifo();
			sleep(3);
		}
	}
	/* proces macierzysty */
	else {
		wrfifo();
	}
	logs("end main");
	return (0);
}
