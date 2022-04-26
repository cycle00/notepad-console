// file.cpp : Contains all methods handling files.
//

#include "file.h"

#include <fstream>

enum class format_type {
	UNSPECIFIED, NIX, DOS, MAC
};

struct line {
	char* data;
	size_t lineno;
	struct line* next;
	struct line* prev;
};

struct openfilestruct {
	char* filename;
	line* filetop, *filebottom, *currenttop, *currentline;
	size_t totalsize;
	size_t firstcol;
	size_t current_x, current_y;
	size_t desired_x;
	format_type fmt;
	bool modified;

	// highlighting/marking
	// the undo stuff when i get to it
};

openfilestruct* openfile;

line* make_node(line* prevnode) {
	line* node = new line;

	node->prev = prevnode;
	node->next = NULL;
	node->data = NULL;
	node->lineno = (prevnode) ? prevnode->lineno + 1 : 1;

	return node;
}

void fm::new_buffer() {
	openfilestruct* node = new openfilestruct;

	openfile = node;

	openfile->filename = "";

	openfile->filetop = make_node(NULL);
	openfile->filetop->data = "";
	openfile->filebottom = openfile->filetop;

	openfile->currentline = openfile->filetop;
	openfile->current_x = 0;
	openfile->current_y = 0;
	openfile->desired_x = 0;

	openfile->currenttop = openfile->filetop;
	openfile->firstcol = 0;

	openfile->totalsize = 0;
	openfile->fmt = format_type::UNSPECIFIED;

	openfile->modified = false;

	// TODO : highlighting/marking and undoing

}

// crop title to fit

// verify file path

// open buffer

// set modified

// execute commands

// prepare for display

// update statusbar

// close buffer

// encode data

// read file

// open file

// check if dir is writable

// write to disk