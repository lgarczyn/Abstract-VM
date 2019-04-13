#include <exception>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "VM.hpp"
#include "Exceptions/VMException.hpp"
#include "Libs/Argument_helper.hpp"

const std::string WHITE = "\e[1;37m";
const std::string GRAY = "\e[0;37m";
const std::string DARK_GRAY = "\e[2;37m";
const std::string PURPLE = "\e[1;35m";
const std::string GREEN = "\e[1;32m";
const std::string RED = "\e[1;31m";
const std::string RESET = "\e[0;0m";
const std::string ENDL = RESET + "\n";

void run(const std::string &file, std::istream &f, bool write, bool debug)
{
	std::string line;
	VM vm;
	size_t line_num = 0;

	std::cout << WHITE << "\n--- <" << file << "> ---\n" << ENDL;

	while (std::getline(f, line))
	{
		line_num++;

		std::string op_string;
		if (write)
		{
			std::cout << PURPLE << std::setw(4) << line_num << ": " << DARK_GRAY << line << ENDL;
		}
		try
		{
			auto [output_str, debug_str] = vm.run_line(line);
			if (debug && debug_str.size())
			{
				std::cout << GREEN << std::setw(4) << line_num << ": " << GRAY << debug_str << ENDL;
			}
			std::cout << output_str;
		}
		catch (VMException &e)
		{
			std::cerr << RED << std::setw(4) << line_num << ": " << e.toString() << ENDL;
		}

		if (line.find(";;") != std::string::npos)
			break;
	}
	try
	{
		vm.checkExit();
	}
	catch (VMException &e)
	{
		std::cerr << RED << "    : " << e.toString() << ENDL;
	}
}

int main(int argc, char **argv)
{
	dsr::Argument_helper ah;
	bool write = false;
	bool debug = false;
	std::vector<std::string> files;

	ah.set_name("Abstract-VM");
	ah.set_description("A simple interpreter for an assembly language with arbitrary arithmetics");
	ah.set_author("Louis Garczynski (lgarczyn@student.42.fr)");
	ah.set_build_date("May 2019");
	ah.set_version(1.0);

	ah.new_flag("w", "write", "Display every line before running.", write);
	ah.new_flag("d", "debug", "Display every operation and their result.", debug);
	ah.set_string_vector("FILES", "AVM file following the subject syntax", files);

	ah.process(argc, argv);

	if (files.size() == 0)
	{
		run("cin", std::cin, write, debug);
	}
	for (auto file:files)
	{
		std::ifstream f;
		f.open(file);

		if (f.is_open() == false)
			std::cerr << RED << "Error: Could not open file: " << file << std::endl;
		else
			run(file, f, write, debug);
	}
}