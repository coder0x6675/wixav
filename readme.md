# WixAV

> An antivirus based on the early versions of *ClamAV*.

## Description

In short the program recursively traverses a specified directory on a filesystem. Every file found is checked against the virus database and logged to stdout in case of a match.

**Note!** This program is not under active development and was only written for educational purposes.

Process:

1. **File collection:** The first part of the program recursively scans the given directory for scanable files. The standard `filesystem` library is used and automatically handles symlinks, device files and other special filetypes.
1. **Signature loading:** The second part loads the signature database. The format of the signature file and signatures can be found below. Error handling in case of corrupt or invalid database is included.
1. **File scanning:** The last step is to scan the files. This process compares the start of each file against each known signature using multiple threads. Matching files are printed to stdout.

## Features

The antivirus contains multiple features:

- Proper error handling against missuse.
- Clean, readable source code.
- Simple and fast file collection.
- Regex implementation to assure the integrity of signatures.
- Efficient file loading with file/string streams.
- Multithreaded file scanning and signature evaluation.
- Usage of highly performant datastructure such as maps and prefix trees.

## Virus Database Format

The database file (`data/signatures.db`) contains a set of test signatures.

- Each row contains a single virus definition.
- Each signature has a name and a sequence of bytes.
- Rows in the database file follows the format `NAME=BYTES` where
	- `NAME` is the name or identifier of this signature.
	- `BYTES` is the byte pattern of this signature.
- The names cannot exceed 32 characters including the NULL terminator.

The byte sequence has no length limit, and is stored in hexadecimal notation. It also starts at position 0 of the file, meaning a byte sequence of length 50 represents the 25 first bytes of a matching file.

## Compatibility

The program was developed and tested on Ubuntu 18.04 using the included `Makefile`.

