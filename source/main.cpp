
#include <filesystem>
#include "common.hpp"
#include "Scanner.hpp"


int main(int argc, char** argv) {

	// Check arguments for errors
	if (argc < 2) show_usage();
	fs::path here(argv[0]);

	// Collect the files to be scanned
	Scanner scanner;
	for (int i = 1; i < argc; i++)
		scanner.add_path(argv[i]);

	// Load malware signatures from file
	const fs::path database_file("../data/signatures.db");
	fs::path database_path = here.parent_path()/database_file;
	scanner.load_signature_file(database_path);

	// Perform the scan and exit
	scanner.scan_all();
	std::exit(0);
}

