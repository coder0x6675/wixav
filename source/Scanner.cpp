
#include <regex>
#include <string>
#include <vector>
#include <thread>
#include <fstream>
#include <iostream>
#include <iterator>
#include <filesystem>
#include <syncstream>
#include "common.hpp"
#include "Scanner.hpp"
#include "threadutil.hpp"


Scanner::Scanner() : max_name_length(0), max_signature_length(0)
{}


void Scanner::add_file(const fs::path& file) {
	if (fs::is_regular_file(file))
		files.push_back(file);
	else
		warn("file is of special type, skipping " + file.string());
}


void Scanner::add_path(const fs::path& target) {

	// Verifying that the path exists
	if (!fs::exists(target))
		fail(target.string() + " does not exist");

	// If `target` is a directory, recursively add all files
	if (fs::is_directory(target)) {
		for (const auto& entry : fs::recursive_directory_iterator(target, fs::directory_options::skip_permission_denied)) {
			if (entry.is_directory())
				continue;
			else
				add_file(entry.path());
		}
	}

	// Otherwise just add the file
	else add_file(target);
}


void Scanner::add_signature(const std::string& name, const std::string& signature) {

	// Verify that the signature is valid
	static const std::regex name_format(R"(\S{1,32})");
	static const std::regex signature_format(R"([a-fA-F0-9]{2}+)");

	if (!std::regex_match(name, name_format) || !std::regex_match(signature, signature_format)) {
		warn("signature is invalid, skipping " + name);
		return;
	}
	if (names.contains(signature)) {
		warn("signature already exists, skipping " + name);
		return;
	}

	// Add the signature
	if (name.length() > max_name_length)
		max_name_length = name.length();
	if (signature.length() > max_signature_length)
		max_signature_length = signature.length();

	names.insert({signature, name});
	signatures.insert(signature);
}


void Scanner::load_signature_file(const fs::path& path) {

	// Open file
	std::ifstream file(path);
	if (!file.is_open())
		fail("unable to open file " + path.string());

	// Read one line at a time
	const char DELIMITER = '=';
	std::string line;
	while (std::getline(file, line)) {

		// Ignore empty or comment lines
		if (line.empty())
			continue;
		if (line.at(0) == '#')
			continue;

		// Parse and add the signature
		size_t pos = line.find(DELIMITER);
		std::string name = line.substr(0, pos);
		std::string signature = line.substr(pos + 1);

		add_signature(name, signature);
	}
}


std::string Scanner::stringify_bytes(const std::vector<char>& bytes) {

	std::ostringstream hex_stream;
	hex_stream << std::hex << std::setfill('0');
	for (const auto& byte : bytes)
		hex_stream << std::setw(2) << static_cast<int>(static_cast<unsigned char>(byte));

	return hex_stream.str();
}


void Scanner::scan_one(const fs::path& path) {

	// Open the file
	std::ifstream file(path.string());
	if (! file.is_open()) {
		warn("unable to open file, skipping " + path.string());
		return;
	}

	// Read as many bytes as the longest signature
	std::vector<char> buffer(max_signature_length / 2);
	file.read(buffer.data(), buffer.size());

	// Stringify the signature
	std::string file_signature = stringify_bytes(buffer);

	// Check if file matches signature, print result
	std::string result(signatures.find(file_signature));
	if (!result.empty())
		std::osyncstream(std::cout)
			<< "[FOUND] "
			<< std::setw(max_name_length)
			<< names[result]
			<< " : "
			<< path.string()
			<< std::endl;
}


void Scanner::scan_all() {

	// Initialize thread parameters
	int task_count = files.size();
	int thread_count = threadutil::get_optimal_thread_count(task_count);
	int tasks_per_thread = threadutil::get_tasks_per_thread(task_count, thread_count);
	int remaining_tasks  = threadutil::get_remaining_tasks(task_count, thread_count);

	// Define the thread work
	auto thread_work = [this](size_t start, size_t range) {
		for (size_t i = start; i < start + range; i++)
			scan_one(files[i]);
	};

	// Start the threads
	std::vector<std::jthread> thread_pool(thread_count);
	for (int i = 0; i < thread_count; i++)
		thread_pool[i] = std::jthread(
			thread_work,
			threadutil::get_segment_start(i, tasks_per_thread, remaining_tasks),
			threadutil::get_segment_range(i, tasks_per_thread, remaining_tasks)
		);
}

