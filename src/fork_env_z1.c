/**
 * Zadania
 * -------
 * z1: Napisz program, który pokazuje, które atrybuty procesu macierzystego są dziedziczone przez proces potomny  uruchomiony za pomocą funkcji fork(), które zaś otrzymują nową wartość.
 * z2: Napisz program, który pokazuje, które atrybuty procesu są zachowane przez proces po wykonaniu funkcji exec().
 * z3: Napisz program, który wyświetla identyfikator procesu (PID) i nazwę związanego z nim polecenia dla wszystkich procesów uruchomionych przez użytkownika podanego w wierszu wywołania programu. Wskazówka: informacje te można uzyskać przeglądając katalog /proc z plików (interesują nas katalogi, których właścicielem jest dany  użytkownik) i pliki /proc/PID/status
 *
 * Każdy proces charakteryzuje się pewnymi atrybutami. Należą do nich:
 * Identyfikator procesu PID
 * Identyfikator procesu macierzystego PPID
 * Rzeczywisty identyfikator właściciela procesu
 * Rzeczywisty identyfikator grupy procesu
 * Efektywny identyfikator właściciela procesu
 * Efektywny identyfikator grupy procesu
 * Katalog bieżący i katalog główny
 * Maska tworzenia pliku
 * Identyfikator sesji
 * Terminal sterujący
 * Deskryptory otwartych plików
 * Ustalenia dotyczące obsługi sygnałów
 * Ustawienia zmiennych środowiskowych
 * Ograniczenia zasobów
 *
 *
 * Potomek dziedziczy z procesu potomnego wiele własności:
 rzeczywisty identyfikator użytkownika, rzeczywisty identyfikator grupy, obowiązujący identyfikator użytkownika, obowiązujący identyfikator grupy,
 identyfikatory dodatkowych grup,
 identyfikator sesji,
 terminal sterujący,
 sygnalizator ustanowienia identyfikatora użytkownika oraz sygnalizator ustanowienia identyfikatora grupy,
 deskryptory otwartych plików (są kopiowane)
 bieżący katalog roboczy,
 katalog główny,
 maskę tworzenia plików,
 maskę sygnałów oraz dyspozycje obsługi sygnałów,
 sygnalizator zamykania przy wywołaniu funkcji exec (close-on-exec) dla wszystkich otwartych deskryptorów plików,
 środowisko,
 przyłączone segmenty pamięci wspólnej,
 ograniczenia zasobów systemowych.
 Są jednak pewne różnice między procesem macierzystym a potomnym:
 wartość powrotu z funkcji fork,
 różne identyfikatory procesów,
 inne identyfikatory procesów macierzystych - w procesie potomnym jest to identyfikator procesu macierzystego; w procesie macierzystym identyfikator procesu macierzystego nie zmienia się,
 w procesie potomnym wartości tms_utime, tms_cutime i tms_ustime są równe 0,
 potomek nie dziedziczy rygli plików, ustalonych w procesie macierzystym,
 w procesie potomnym są zerowane wszystkie zaległe alarmy,
 w procesie potomnym jest zerowany zbiór zaległych sygnałów.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

extern char** environ;
char *prt_parent;

int glob = 1; 			// zewnętrzna zmienna

/* Prints the environment, one environment variable to a line, of the
 process given by PID. */
char *print_process_environment(pid_t pid) {
	int fd;
	char filename[24];
	char environment[8192];
	size_t length;
	char* next_var;
	/* Generate the name of the environ file for the process. */
	snprintf(filename, sizeof(filename), "/proc/%d/environ", (int) pid);
	/* Read the contents of the file. */
	fd = open(filename, O_RDONLY);
	length = sizeof(environ);
	printf("Size of environ: %d\n", length);
	close(fd);
	/* read does not NUL-terminate the buffer, so do it here. */
	environment[length] = '\0';
	/* Loop over variables. Variables are separated by NULs. */
	next_var = environment;
	while (next_var < environment + length) {
		/* Print the variable. Each is NUL-terminated, so just treat it
		 like an ordinary string. */
		printf(">> %s\n", next_var);
		/* Advance to the next variable. Since each variable is
		 NUL-terminated, strlen counts the length of the next variable,
		 not the entire variable list. */
		next_var += strlen(next_var) + 1;
	}
	return (environment);
}

//int main(int argc, char* argv[]) {
//pid_t pid = (pid_t) atoi (argv[1]);
//print_process_environment (pid);
///return 0;
//}

int main1(int argc, char **argv) {
	int var = 100; 		        // zmienna automatyczna na stows
	char **env = environ;		// środowisko parent
	// zapamiętanie environ w tablicy

	printf("PROGRAM Z1\n\n");
	printf("Zmienne srodowiskowe parent: ----------------------------\n");
	while (*env) {
		printf("%s\n", *env++);
	}

	printf("---------------------------------------------------------\n");

	//for (int i = 0; *env != NULL && gets(env[i]); i++)
	//	prt_parent[i] = env[i];

	pid_t pid = fork();

	if (pid == 0) {
		// child process
		glob++;
		var++;
		printf("child process: pid %d, ppid %d, getuid %d, geteuid %d, getgid %d, glob = %d, var = %d\n", getpid(), getppid(), getuid(), geteuid(), getgid(),
				glob, var);

		/**
		 * wy swietlenie zmiennych środowiskowych różnych od parent
		 */
		printf("Zmienne srodowiskowe child różne od parent:\n");
		char environment_1[8192];
		char * prt_env = &environment_1;
		prt_env = print_process_environment(pid);
		char **env_child = environ;
		printf("Size of *char: %d\n", sizeof(environ));

		while (*env_child) {
			printf("compare - %s %d\n", *env_child, strcmp(*env_child++, *env++));
			//printf("%s -----\n", *env2++);
			//if (strcmp(*env2, ++*env) == 0) {
			//
			//} else {
			//printf("%s jest takie samo\n", *env2);
			//}
			//*env_child++;
			//*env++;
		}
		printf("-------------------- x --------------------\n");

	} else if (pid > 0) {
		// parent process
		printf("parent process: pid %d, ppid %d, getuid %d, geteuid %d, getgid %d, glob = %d, var = %d\n", getpid(), getppid(), getuid(), geteuid(), getgid(),
				glob, var);
	} else {
		// fork failed
		printf("fork() failed!\n");
		return (1);
	}

	printf("-- end of program pid %d\n", getpid());

	return (0);
}

