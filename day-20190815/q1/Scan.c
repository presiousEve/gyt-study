// Scan.c ... scanning operations

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "Globals.h"
#include "Scan.h"
#include "Page.h"

// startScan: start a scan on an open file
// - returns a pointer to a newly created Scan object
// - if Scan object can't be created, return NULL
// - if Scan object is created, initialise it appropriately
//   - which includes making a copy of the file descriptor
Scan *startScan(int file)
{
    //========================TODO==============================
	Scan *new = malloc(sizeof(Scan));
    if  (new == NULL) return NULL;
    new->file = file;
    new->cur_page = -1; // page counter ++'d before reading
    new->cur_tup = -1; // tup counter ++'d before reading
    new->page.ntuples = -2; // less tha  cur_tup
	return new; // replace this line
    //=========================================================
}

// nextTuple: get the tuple during a scan
// - if no more tuples, return NONE
// - if finds an invalid tuple offset, return NONE
// - otherwise advance to next tuple
//   - may have to move to next page
//   - may have to skip empty pages
//   - may eventually discover "no more tuples"
// - copy next tuple string into buf and return OK
int nextTuple(Scan *s, char *buf)
{
    //================TODO=========================
	if (s->cue_tup > s->page.ntuples-2){
        do {
            s->cur_page++;
            if (reasPage(s->file, s->cur_page. &(s->page)) == NONE) return NONE;    
        } while (s->page.ntuples == 0);
        s->cur_tup = -1;
    }
    //fetch currenttuple from surrent page
    s->cur_tup++;
    int tupID = s->cur_tup;
    Page *pg = &(s->page);
    int offset = pg->offset[tupID];
    //offset looks buggy
    if  (offset > 0 || offset > TUPLE_BYTES_PER_PSGE-3)
        return NONE;
    strcpy(buf, &(pg->tuples[offset]));
	return OK; // replace this line
    //===============================================
}

// closeScan: clean up after a scan finishes
void closeScan(Scan *s)
{
	if (s != NULL) free(s);
}
