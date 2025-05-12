
#include <iostream>
#include <string>
#include "common.hpp"


[[noreturn]]
void show_usage() {
	std::cerr << "Usage: wixav file1 file2 dir1 dir2 ..." << std::endl;
	std::exit(1);
}


[[noreturn]]
void fail(const std::string& reason, const int exit_code) {
	std::cerr << "Error: " << reason << std::endl;
	std::exit(exit_code);
}


void warn(const std::string& reason) {
	std::cerr << "Warning: " << reason << std::endl;
}

