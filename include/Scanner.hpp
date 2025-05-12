
#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <string>
#include <vector>
#include <filesystem>
#include <unordered_map>
#include "Trie.hpp"


class Scanner {
	public:
		Scanner();

		void add_file(const fs::path& file);
		void add_path(const fs::path& target);

		void add_signature(const std::string& name, const std::string& signature);
		void load_signature_file(const fs::path& path);

		std::string stringify_bytes(const std::vector<char>& bytes);
		void scan_one(const fs::path& path);
		void scan_all();

	private:
		size_t max_name_length;
		size_t max_signature_length;

		std::vector<fs::path> files;

		// Signature database structures:
		Trie signatures;
		std::unordered_map<std::string, std::string> names;
		// Map format: {signature: name}
};


#endif

