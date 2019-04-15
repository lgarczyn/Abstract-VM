#include "Exceptions/VMException.hpp"
#include "Libs/Argument_helper.hpp"
#include "VM.hpp"

#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>

const std::string WHITE = "\e[1;37m";
const std::string GRAY = "\e[0;37m";
const std::string DARK_GRAY = "\e[2;37m";
const std::string PURPLE = "\e[1;35m";
const std::string GREEN = "\e[1;32m";
const std::string RED = "\e[1;31m";
const std::string RESET = "\e[0;0m";
const std::string ENDL = RESET + "\n";


// Handle VM launch and return values, display any relevant info
void run( bool standardInput, std::istream& stream, bool write, bool debug )
{
	std::string line;
	VM vm;
	size_t lineNum = 0;

	while ( std::getline( stream, line ) )
	{
		lineNum++;

		// Display read line
		if ( write )
		{
			std::cout << PURPLE << std::setw( 4 ) << lineNum << ": " << DARK_GRAY << line << ENDL;
		}
		try
		{
			// Run instruction, and get display and debug output
			auto [ outputStr, debugStr ] = vm.runLine( line );
			if ( debug && debugStr.size() )
			{
				std::cout << GREEN << std::setw( 4 ) << lineNum << ": " << GRAY << debugStr << ENDL;
			}
			std::cout << outputStr;
		}
		catch ( VMException& e )
		{
			// Display any expected error
			std::cerr << RED << std::setw( 4 ) << lineNum << ": " << e.toString() << ENDL;
		}

		// Quit if received standard input EOF symbol
		if ( standardInput && line.find( ";;" ) != std::string::npos )
			break;
	}
	try
	{
		vm.checkExit();
	}
	catch ( VMException& e )
	{
		std::cerr << RED << "    : " << e.toString() << ENDL;
	}
}

int main( int argc, char** argv )
{
	dsr::Argument_helper ah;
	bool write = false;
	bool debug = false;
	std::vector<std::string> files;

	// Setup Argument Helper

	ah.set_name( "Abstract-VM" );
	ah.set_description(
		"A simple interpreter for an assembly language with arbitrary arithmetics" );
	ah.set_author( "Louis Garczynski (lgarczyn@student.42.fr)" );
	ah.set_build_date( "May 2019" );
	ah.set_version( 1.0 );

	ah.new_flag( "w", "write", "Display every line before running.", write );
	ah.new_flag( "d", "debug", "Display every operation and their result.", debug );
	ah.set_string_vector( "FILES", "AVM file following the subject syntax", files );

	ah.process( argc, argv );

	// Open files or standard input, and start vm

	if ( files.size() == 0 )
	{
		run( true, std::cin, write, debug );
	}
	for ( auto file : files )
	{
		std::ifstream f;
		f.open( file );

		std::cout << WHITE << "\n--- <" << file << "> ---\n" << ENDL;

		if ( f.is_open() == false )
			std::cerr << RED << "Error: Could not open file: " << file << std::endl;
		else
			run( false, f, write, debug );
	}
}