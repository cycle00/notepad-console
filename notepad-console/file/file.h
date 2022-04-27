#pragma once

#include <stdlib.h>
#include <string>

/* filemanager */
namespace fm {
	void new_buffer();
	bool open_buffer(const char* filename, bool new_file);
	
};