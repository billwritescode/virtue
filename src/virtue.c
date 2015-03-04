/***************************************************************
 *****Virtue, a chess playing engine derived from VICE 1.1******
 ****Credit and thanks to BlueFeverSoft, developer of VICE******
 *******************Developed by Bill Garate********************
 ******************Licensed under MIT License*******************
 ***************************************************************
 * FILE NAME: virtue.c                                         *
 * PURPOSE: Play chess in various capacities                   *
 * SUPPORTS:                                                   *
 * 	Protocols: UCI, Xboard                                     *
 * OPTIONS:                                                    *
 *	Flag			Usage									   *
 *	-d				turn on debug mode						   *
 ***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"
#include "fen.h"

int main(int argc, char **argv) {

	AllInit(argc, argv);		/*	Changes debug to TRUE if 
								*	command-line argument is
								*	passed
								*/

	S_BOARD pos[1];
    S_SEARCHINFO info[1];
    info->quit = FALSE;
	pos->HashTable->pTable = NULL;
    InitHashTable(pos->HashTable, 64);
	setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    
	printf("debug=%d\n",debug);



	printf("Welcome to Vice! Type 'vice' for console mode...\n");

	char line[256];
	while (TRUE) {
		memset(&line[0], 0, sizeof(line));

		fflush(stdout);
		if (!fgets(line, 256, stdin))
			continue;
		if (line[0] == '\n')
			continue;
		if (!strncmp(line, "uci",3)) {
			Uci_Loop(pos, info);
			if(info->quit == TRUE) break;
			continue;
		} else if (!strncmp(line, "xboard",6))	{
			XBoard_Loop(pos, info);
			if(info->quit == TRUE) break;
			continue;
		} else if (!strncmp(line, "vice",4))	{
			Console_Loop(pos, info);
			if(info->quit == TRUE) break;
			continue;
		} else if(!strncmp(line, "quit",4))	{
			break;
		}
	}

	free(pos->HashTable->pTable);
	CleanPolyBook();
	return 0;
}








