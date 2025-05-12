
#include <string>
#include <sstream>
#include "Trie.hpp"


Trie::Trie() : is_string_(false) {}


void Trie::insert(const std::string& s) {

	Trie* cur = this;
	for (char c : s) {
		if (!cur->children_.contains(c))
			cur->children_[c] = new Trie();
		cur = cur->children_[c];
	}

	cur->is_string_ = true;
}


std::string Trie::find(const std::string& s) {

	std::ostringstream prefix;

	Trie* cur = this;
	for (char c : s) {
		prefix << c;
		if (!cur->children_.contains(c))
			break;
		cur = cur->children_[c];
		if (cur->is_string_)
			return prefix.str();
	}

	return "";
}

