#include <asm-generic/errno-base.h>

/**
 * Uzupełnij program shell z o „ręczną” obsługę potoków.
 * ----------------------------------------------------
 * Napisz program, który zbiera komunikaty od wielu programów i wyświetla je na ekranie. Do komunikacji użyj potoku nazwanego.
 *
 * Wskazówka: Utwórz program rdfifo, którego zadaniem jest utworzenie kolejki FIFO i czytanie z niej danych.
 * Utwórz program wrfifo, który otwiera kolejkę FIFO tylko do zapisu i wpisuje do niej dane (np. swoj pid i czas).
 *
 * Q: W jaki sposób przekażesz wspólną nazwę kolejki FIFO do tych programów?
 * A: przez zmienną statyczą
 *
 * Q: W jaki sposób zapewnić działanie programu zbierającego komunikaty również wtedy, kiedy nie ma programu piszącego do łącza?
 * A: przez proces pętli nieskończonej ze sleep
 *
 * Q: Jak zapewnić to, że komunikaty pochodzące od różnych programów wyświetlane są w całości, tzn. nie są rozdzielane  komunikatami od innych programów?
 * A: flush? (do sprawdzenia).
 *
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
#include <time.h>

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
 * Serwer read from named pipe
 * -----------------
 * @param argc
 * @param argv
 * @return
 */
int rdfifo() {

	int fifo, var;

	/* There are *two* ways the open can fail: the pipe doesn't exist
	 * yet, *or* it succeeded, but a different writer already opened
	 * it but didn't yet remove it.
	 */
	logs("reader start");
	while (1) {
		logs("while1");
		while ((fifo = open(FIFO, O_RDONLY)) == -1) {
			/* Since you didn't specify O_CREAT in the call to open, there
			 * is no way that FIFO would have been created by the
			 * reader.  If there *is* now a FIFO, a remove here
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
	logs("Remove FIFO");
	remove(FIFO);
	while ((var = read(fifo, buf, BUFFERSIZE)) > 0) {
		printf("[%s](pid %d) DEBUG: Passed %s %d : reader reads record: %s", __TIME__, (int) getpid(), __FUNCTION__, __LINE__, buf);
		/* No need to sleep; we'll consume input as it becomes available. */
	}

	close(fifo);
	logs("EOF reader");
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
int wrfifo(pid_t pid) {
	// time structs
	time_t rawtime;
	struct tm * timeinfo;

	int len, i;
	char buf[PIPE_BUF];
	int fd;
	int communicates = 0;

//	if ((unlink(FIFO)) == -1) {
//		logs("Error unlink FIFO")
//	} else {
//		logs("unlink fifo");
//	}

	if ((mkfifo(FIFO, FIFO_PERMS) == -1) && (errno != EEXIST)) {
		logs("Server failed to create a FIFO");
		return (1);
	} else if (errno == ENOENT) {
		printf("[%s](pid %d) DEBUG: Passed %s %d : No such file or directory - mkfifo errno: %d\n", __TIME__, (int) getpid(), __FUNCTION__, __LINE__, errno);
	} else if (errno == EEXIST) {
		printf("[%s](pid %d) DEBUG: Passed %s %d : mkfifo exist: %d\n", __TIME__, (int) getpid(), __FUNCTION__, __LINE__, errno);
	} else {
		printf("[%s](pid %d) DEBUG: Passed %s %d : No such file or directory - mkfifo errno: %d\n", __TIME__, (int) getpid(), __FUNCTION__, __LINE__, errno);
	}

	if ((fd = open(FIFO, O_WRONLY)) == -1) {
		logs("Client failed to open log fifo for writing");
		return (1);
	} else {
		logs("pipe opened to read-write");
	}

	/**
	 * write some text to pipe
	 */
	for (i = 0; i < 10; i++) {
		sleep(1);
		//logs("time")
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		sprintf(buf, "#%d test PID: %d: text -> %s", communicates++, (int) getpid(), asctime(timeinfo));
		len = strlen(buf);
		if (write(fd, buf, len) != len) {
			logs("Client failed to write");
			return (1);
		} else {
			printf("[%s](pid %d) DEBUG: Passed %s %d : client succesed write to pipe: %s", __TIME__, (int) getpid(), __FUNCTION__, __LINE__, buf);
		}
	}
	/* Wait for the child process to finish. */
	waitpid(pid, NULL, 0);
	sleep(1);
	logs("close fd");
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

	/**
	 * analiza lini komend
	 *
	 */
	int opt = 0;
	char *in_fname = NULL;
	char *out_fname = NULL;

	/**
	 * funkcje programu
	 */
	while ((opt = getopt(argc, argv, "rwh")) != -1) {
		switch (opt) {
		case 'r':
			in_fname = optarg;
			printf("\nInput option value=%s set program read from FIFO", in_fname);
			rdfifo();
			exit(0);
			break;
		case 'w':
			out_fname = optarg;
			printf("\nInput option value=%s set program to write to FIFO", out_fname);
			wrfifo(pid);
			exit(0);
			break;
		case '?':
		case 'help':
		case 'h':
		default:
			printf("\nProgram FIFO\n");
			printf("------------\n");
			printf("Program bez argumentów tworzy named pipe a w procesie potomnym zapisuje do niego dane.\n");
			printf("Program mozna wywołać z argumentami tak aby działał jako odczyt (r) z pipe lub zapis do pipe (w).\n");
			printf("Zapisywane są do pipe couner, PID i curenttime.\n\n");
			printf("Usage: %s [-r] [-w]\n\n", argv[0]);

			exit(0);
			break;
		}
	}

	logs("start program");

	pid = fork();

	/* proces potomny */
	if (pid == (pid_t) 0) { /* brak obsługi błędów */
		/**
		 * Odczytywanie
		 */
		for (i = 0; i < 3; i++) {
			rdfifo();
			sleep(1);
		}
	}
	/* proces macierzysty */
	else {
		for (i = 0; i < 5; i++) {
			wrfifo(pid);

		}
	}
	logs("end main");
	return (0);
}
