/* 
 * Virtue: better than VICE
 * File: fen.c
 * Usage: Proceses Forsythe-Edwards Notation (fen) strings.
 * Functions:
 * 		ParseFen(char* fen, S_BOARD* pos)
 */
 
/**********IMPORTS***********/
#include "defs.h"
 
/**********FUNCTIONS**********/

/* Function: ParseFen(char* fen, S_BOARD* pos)
 *
 * *****Purpose******
 * Set up the board representation to a given position
 *
 * ****Arguments****
 * Identifier		Description							Assumptions
 * char* fen 		Pointer to a FEN position string	Well-formed
 * S_BOARD* pos		Pointer to a board representation	Well-formed
 *
 * *****Output******
 * Type		Value	Meaning
 * int		0		Operation successful
 * int		-1 		Operation failure: Invalid FEN String
 * 
 * More information about Forsythe-Edwards Notation
 * http://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
 * 
 *****************************************************************/
 
 
int ParseFen(char *fen, S_BOARD *pos) {

	ASSERT(fen!=NULL); ASSERT(pos!=NULL);	// Debug ASSERTs
	
	/*  Locals */ 
	int  rank = RANK_8;
    int  file = FILE_A;
    int  piece = 0;
    int  count = 0;
    int  i = 0;
	int  sq64 = 0;
	int  sq120 = 0;

	/* First, reset the board to no position */
	ResetBoard(pos);

	while ((rank >= RANK_1) && *fen) {
	    count = 1;
		switch (*fen) {
            case 'p': piece = bP; break;
            case 'r': piece = bR; break;
            case 'n': piece = bN; break;
            case 'b': piece = bB; break;
            case 'k': piece = bK; break;
            case 'q': piece = bQ; break;
            case 'P': piece = wP; break;
            case 'R': piece = wR; break;
            case 'N': piece = wN; break;
            case 'B': piece = wB; break;
            case 'K': piece = wK; break;
            case 'Q': piece = wQ; break;

            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
                piece = EMPTY;
                count = *fen - '0';
                break;

            case '/':
            case ' ':
                rank--;
                file = FILE_A;
                fen++;
                continue;

            default:
                printf("FEN error \n");
                return -1;
        }

		for (i = 0; i < count; i++) {
            sq64 = rank * 8 + file;
			sq120 = SQ120(sq64);
            if (piece != EMPTY) {
                pos->pieces[sq120] = piece;
            }
			file++;
        }
		fen++;
	}

	ASSERT(*fen == 'w' || *fen == 'b');

	pos->side = (*fen == 'w') ? WHITE : BLACK;
	fen += 2;

	for (i = 0; i < 4; i++) {
        if (*fen == ' ') {
            break;
        }
		switch(*fen) {
			case 'K': pos->castlePerm |= WKCA; break;
			case 'Q': pos->castlePerm |= WQCA; break;
			case 'k': pos->castlePerm |= BKCA; break;
			case 'q': pos->castlePerm |= BQCA; break;
			default:	     break;
        }
		fen++;
	}
	fen++;

	ASSERT(pos->castlePerm>=0 && pos->castlePerm <= 15);

	if (*fen != '-') {
		file = fen[0] - 'a';
		rank = fen[1] - '1';

		ASSERT(file>=FILE_A && file <= FILE_H);
		ASSERT(rank>=RANK_1 && rank <= RANK_8);

		pos->enPas = FR2SQ(file,rank);
    }

	pos->posKey = GeneratePosKey(pos);

	UpdateListsMaterial(pos);

	return 0;
}
