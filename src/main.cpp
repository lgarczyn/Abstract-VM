#include <exception>
#include <iostream>
#include <fstream>
#include "VM.hpp"
#include "Exceptions/VMException.hpp"

void run(const char *prog, const char *file, std::istream &f)
{
	(void)prog;
	size_t line_counter = 0;
	std::string line;
	VM vm;

	std::cout << "--- <" << file << "> ---" << std::endl;

	while (std::getline(f, line))
	{
		line_counter++;
		try
		{
			vm.run_line(line);
		}
		catch (VMException &e)
		{
			std::cerr << "\e[3;31mError:\e[37m Line " << line_counter << ": " << e.toString() << std::endl;
		}
		catch (std::exception &e)
		{
			std::cerr << "\e[3;31mUnexpected Error:\e[37m Line " << line_counter << ": " << e.what() << std::endl;
		}

		if (line.find(";;") != std::string::npos)
			break;
	}
	try
	{
		vm.check_exit();
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

int main(int argc, char **argv)
{
	if (argc == 1)
	{
		run(argv[0], "cin", std::cin);
	}
	for (int i = 1; i < argc; i++)
	{
		std::ifstream f;
		f.open(argv[i]);

		if (f.is_open() == false)
			std::cerr << argv[0] << ": Could not open file: " << argv[i] << std::endl;
		else
			run(argv[0], argv[i], f);
	}
}