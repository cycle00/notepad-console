// file.cpp : Contains all methods handling files.
//

#include "file.h"

#include <direct.h>
#include <fstream>
#include <io.h>
#include <iostream>
#include <limits>
#include <string>
#include <Windows.h>

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

line* make_new_node(line* prevnode) {
	line* node = new line;

	node->prev = prevnode;
	node->next = nullptr;
	node->data = nullptr;
	node->lineno = (prevnode) ? prevnode->lineno + 1 : 1;

	return node;
}

void fm::new_buffer() {
	openfilestruct* node = new openfilestruct;

	openfile = node;

	openfile->filename = "";

	openfile->filetop = make_new_node(nullptr);
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

std::string get_full_path(const char* filename) {
	char buffer[_MAX_PATH];
	_getcwd(buffer, _MAX_PATH);
	std::string path(buffer);
	path.append("\\").append(filename);
	return path;
}

bool fm::open_buffer(const char* filename, bool new_file) {
	char* full_path = new char[get_full_path(filename).length() + 1];
	strcpy(full_path, get_full_path(filename).c_str());

	WIN32_FILE_ATTRIBUTE_DATA fileinfo;
	int result = 0;
	
	FILE* f;

	// don't open directories
	if (*filename != '\0' && GetFileAttributesEx(full_path, GetFileExInfoStandard, &fileinfo) != 0) {
		if (fileinfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			// notify
			delete[] full_path;
			return false;
		}
		if (fileinfo.dwFileAttributes & FILE_ATTRIBUTE_READONLY) {
			// readonly
		}
	}

	new_buffer();

	if (filename[0] != '\0') {
		result = open_file(full_path, new_file, &f);
	}

	if (result > 0) {
		// read_file(f, result, full_path, !new_file)
	}

	if (result >= 0 && new_file) {
		openfile->filename = new char[sizeof(filename) / sizeof(filename[0])];
		strcpy(openfile->filename, filename);
		openfile->currentline = openfile->filetop;
		openfile->current_x = 0;
		openfile->desired_x = 0;
	}

	delete[] full_path;

	return true;
}

// set modified

// execute commands

// prepare for display

// update statusbar

// close buffer

// encode data

// read file

int open_file(const char* filename, bool new_file, FILE** f) {
	char* full_filename = new char[get_full_path(filename).length() + 1];
	strcpy(full_filename, get_full_path(filename).c_str());

	WIN32_FILE_ATTRIBUTE_DATA fileinfo;
	int fd;

	if (GetFileAttributesEx(full_filename, GetFileExInfoStandard, &fileinfo) == 0) {
		delete[] full_filename;

		if (new_file) {
			// new file
			return 0;
		}
		else {
			// file not found
			return -1;
		}
	}

	fd = _open(full_filename, _A_RDONLY);

	if (fd == -1) {
		if (errno == EINTR || errno == 0) {
			// interrupted
		}
		else {
			// error reading file
		}
	}
	else {
		*f = _fdopen(fd, "rb");

		if (*f == nullptr) {
			// error reading file
			_close(fd);
			fd = -1;
		}
	}

	delete[] full_filename;

	return fd;
}

// check if dir is writable

// write to disk