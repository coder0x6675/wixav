
#ifndef TRIE_HPP
#define TRIE_HPP

#include <string>
#include <unordered_map>


class Trie {
	public:
		Trie();

		void insert(const std::string& s);
		std::string find(const std::string& s);

	private:
		bool is_string_;
		std::unordered_map<char, Trie*> children_;
};


#endif

