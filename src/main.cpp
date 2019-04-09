#include <exception>
#include <iostream>
#include <fstream>
#include "VM.hpp"

void run(const char *prog, const char *file, std::istream &f)
{
	size_t line_counter = 0;
	std::string line;
	VM vm;

	while (std::getline(f, line))
	{
		line_counter++;
		try
		{
			vm.run_line(line);
		}
		catch (std::exception &e)
		{
			std::cerr << prog << ": " << file << " line " << line_counter << ": " << e.what() << std::endl;
		}

		if (line.find(";;") != std::string::npos)
			break;
	}
	vm.check_exit();
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