// runBSTree.c - a command-line interface to the BSTree ADT

// !!! DO NOT MODIFY THIS FILE !!!

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BSTree.h"

#define MAX 1024

static void processOptions(int argc, char *argv[]);
static void showUsage(char *progname);
static void showWelcomeMessage(void);
static int getCommand(char *buf);
static char **tokenize(char *s, int *ntokens);
static void freeTokens(char **tokens);
static void showHelp(void);

static void runInsert(BSTree *t, int argc, char *argv[]);
static void runFind(BSTree *t, int argc, char *argv[]);
static void runPrint(BSTree *t, int argc, char *argv[]);
static void runNumNodes(BSTree *t, int argc, char *argv[]);
static void runNumLeaves(BSTree *t, int argc, char *argv[]);
static void runDeleteLeaves(BSTree *t, int argc, char *argv[]);
static void runInOrder(BSTree *t, int argc, char *argv[]);
static void runPreOrder(BSTree *t, int argc, char *argv[]);
static void runPostOrder(BSTree *t, int argc, char *argv[]);
static void runLevelOrder(BSTree *t, int argc, char *argv[]);
static void showCmdHelp(void);

////////////////////////////////////////////////////////////////////////

typedef struct command {
	char  *code;
	void (*fn)(BSTree *, int, char **);
	char  *argHint;
	char  *helpMsg;
} Command;

static Command COMMANDS[] = {
	{"+", runInsert,       "<num>...",  "insert values in the given order"},
	{"f", runFind,         "<num>",     "check if a value is in the tree"},
	{"p", runPrint,        "",          "print the tree"},
	{"n", runNumNodes,     "",          "get the size of the tree"},
	{"l", runNumLeaves,    "",          "get the number of leaves in the tree"},
	{"d", runDeleteLeaves, "",          "delete all leaves in the tree"},
	{"I", runInOrder,      "",          "print the in-order traversal of the tree"},
	{"P", runPreOrder,     "",          "print the pre-order traversal of the tree"},
	{"O", runPostOrder,    "",          "print the post-order traversal of the tree"},
	{"L", runLevelOrder,   "",          "print the level-order traversal of the tree"},
	{"?", NULL,            "",          "show this message"},
	{"q", NULL,            "",          "quit"},
};

////////////////////////////////////////////////////////////////////////

static bool ECHO = false;
static Command *currCommand = NULL;

int main(int argc, char *argv[]) {
	processOptions(argc, argv);
	showWelcomeMessage();

	BSTree t = BSTreeNew();
	bool done = false;
	char cmd[MAX] = {0};

	while (!done && getCommand(cmd)) {
		if (ECHO) {
		    printf("%s", cmd);
		}

		int ntokens = 0;
		char **tokens = tokenize(cmd, &ntokens);
		if (ntokens == 0) {
			free(tokens);
			continue;
		}
		
		char *cmdName = tokens[0];

		// Meta-commands
		if (strcmp(cmdName, "?") == 0) {
			showHelp();
		} else if (strcmp(cmdName, "q") == 0) {
			done = true;
		
		// Actual commands
		} else {
			bool validCommand = false;

			int numCommands = sizeof(COMMANDS) / sizeof(Command);
			for (int i = 0; i < numCommands; i++) {
				if (strcmp(cmdName, COMMANDS[i].code) == 0) {
					validCommand = true;
					currCommand = &COMMANDS[i];
					COMMANDS[i].fn(&t, ntokens, tokens);
				}
			}

			if (!validCommand) {
				printf("Unknown command '%s'\n", cmdName);
			}
		}
		freeTokens(tokens);
	}

	BSTreeFree(t);
}

static void processOptions(int argc, char *argv[]) {
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-e") == 0) {
			ECHO = true;
		} else {
			showUsage(argv[0]);
			exit(EXIT_FAILURE);
		}
	}
}

static void showUsage(char *progName) {
	printf("Usage: %s [options]...\n"
	       "Options:\n"
	       "    -h      show this help message\n"
	       "    -e      echo - echo all commands\n",
	       progName);
}

static void showWelcomeMessage(void) {
	printf("Interactive BSTree Tester\n");
	printf("Enter ? to see the list of commands.\n");
}

static int getCommand(char *buf) {
	printf("> ");
	return (fgets(buf, MAX, stdin) != NULL);
}

static char **tokenize(char *s, int *ntokens) {
	char *separators = " \t\n";
	*ntokens = 0;

	char **tokens = calloc((strlen(s) + 1), sizeof(*tokens));
	assert(tokens != NULL);

	while (*s != '\0') {
		s += strspn(s, separators);

		if (*s == '\0') {
		    break;
		}

		size_t length = strcspn(s, separators);

		char *token = strndup(s, length);
		assert(token != NULL);
		s += length;

		tokens[*ntokens] = token;
		(*ntokens)++;
	}

	tokens[*ntokens] = NULL;

	tokens = realloc(tokens, (*ntokens + 1) * sizeof(*tokens));
	assert(tokens != NULL);

	return tokens;
}

static void freeTokens(char **tokens) {
	for (int i = 0; tokens[i] != NULL; i++) {
		free(tokens[i]);
	}
	free(tokens);
}

static void showHelp(void) {
	printf("Commands:\n");
	int numCommands = sizeof(COMMANDS) / sizeof(Command);
	for (int i = 0; i < numCommands; i++) {
		printf("%5s %-18s %s\n", COMMANDS[i].code, COMMANDS[i].argHint,
		                         COMMANDS[i].helpMsg);
	}
	printf("\n");
}

////////////////////////////////////////////////////////////////////////
// Commands

static void runInsert(BSTree *t, int argc, char *argv[]) {
	if (argc < 2) {
		showCmdHelp();
		return;
	}

	int elem = 0;
	char c;
	for (int i = 1; i < argc; i++) {
		if (sscanf(argv[i], "%d%c", &elem, &c) != 1) {
			printf("Error: Invalid value '%s'\n", argv[i]);
			return;
		}
	}
	
	for (int i = 1; i < argc; i++) {
		sscanf(argv[i], "%d", &elem);
		*t = BSTreeInsert(*t, elem);
		printf("Inserted %d\n", elem);
	}
}

static void runFind(BSTree *t, int argc, char *argv[]) {
	if (argc != 2) {
		showCmdHelp();
		return;
	}

	int elem = 0;
	char c;
	if (sscanf(argv[1], "%d%c", &elem, &c) != 1) {
		printf("Error: Invalid value '%s'\n", argv[1]);
		return;
	}

	bool result = BSTreeFind(*t, elem);
	printf("%d is%s in the tree\n", elem, result ? "" : " not");
}

static void runPrint(BSTree *t, int argc, char *argv[]) {
	if (argc != 1) {
		showCmdHelp();
		return;
	}
	
	BSTreeShow(*t);
}

static void runNumNodes(BSTree *t, int argc, char *argv[]) {
	if (argc != 1) {
		showCmdHelp();
		return;
	}

	int numNodes = BSTreeNumNodes(*t);
	printf("The tree contains %d %s\n", numNodes,
	       numNodes == 1 ? "node" : "nodes");
}

static void runNumLeaves(BSTree *t, int argc, char *argv[]) {
	if (argc != 1) {
		showCmdHelp();
		return;
	}

	int numLeaves = BSTreeNumLeaves(*t);
	printf("The tree contains %d %s\n", numLeaves,
	       numLeaves == 1 ? "leaf" : "leaves");
}

static void runDeleteLeaves(BSTree *t, int argc, char *argv[]) {
	if (argc != 1) {
		showCmdHelp();
		return;
	}

	*t = BSTreeDeleteLeaves(*t);
	printf("Deleted all the leaves in the tree\n");
}

static void runInOrder(BSTree *t, int argc, char *argv[]) {
	if (argc != 1) {
		showCmdHelp();
		return;
	}

	printf("In-order traversal: ");
	BSTreeInOrder(*t);
	printf("\n");
}

static void runPreOrder(BSTree *t, int argc, char *argv[]) {
	if (argc != 1) {
		showCmdHelp();
		return;
	}

	printf("Pre-order traversal: ");
	BSTreePreOrder(*t);
	printf("\n");
}

static void runPostOrder(BSTree *t, int argc, char *argv[]) {
	if (argc != 1) {
		showCmdHelp();
		return;
	}

	printf("Post-order traversal: ");
	BSTreePostOrder(*t);
	printf("\n");
}

static void runLevelOrder(BSTree *t, int argc, char *argv[]) {
	if (argc != 1) {
		showCmdHelp();
		return;
	}

	printf("Level-order traversal: ");
	BSTreeLevelOrder(*t);
	printf("\n");
}

static void showCmdHelp(void) {
    printf("Usage: %s %s\n", currCommand->code, currCommand->argHint);
}

////////////////////////////////////////////////////////////////////////

