
#ifndef COMMON_HPP
#define COMMON_HPP

#include <string>
#include <filesystem>


namespace fs = std::filesystem;


// Shows program usage and exits with error.
[[noreturn]]
void show_usage();

// Prints message as error and exits with specified code.
[[noreturn]]
void fail(const std::string& reason, const int exit_code = 1);

// Prints message as warning.
void warn(const std::string& reason);


#endif

