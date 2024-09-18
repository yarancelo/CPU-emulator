#pragma warning(disable:4996)
#pragma once

#include <iostream>
#include <cstdint>
#include <stdlib.h>
#include <string.h>

#include "ram.hpp"
#include "cpu.hpp"

#include "ram_load.hpp"


void load_func(CPU::cpu cpu)
{
	char cont;
	std::string option;
	bool valid;
	byte value = 0;
	int temp;
	addr address = 0;
	printf("Memory access interface\n");
	printf("Input memory load option\n");
	while (1)
	{
		std::cin >> option;
		if (option == "help")
		{
			printf("all options:\n\n");
			printf("LFF - load from first address\n");
			printf("ATAA - access to any address and insert data\n");
			printf("LIST - listing of current ram containment\n");
			printf("EXE - finish input and start execution\n");
			printf("help - all options\n");
			printf("EXIT - exit programm\n");
			printf("\n");
			continue;
		}

		else if (option == "LFF")
		{
			printf("Type instructions or data\n");
			while (1)
			{
				printf("Current address = %d\n", address);

				while (1)
				{
					std::cin >> temp;
					if (temp > 255)
					{
						printf("Input invalid (value bigger than 1 byte)\n");
						continue;
					}
					value = (byte)temp;
					break;
				}
				cpu.RAM.write(value, address);
				address++;
				printf("Continue? (Y/N)\n");
				std::cin >> cont;
				if (cont == 'Y')
					continue;
				else
				{
					printf("\nInput memory load option\n");
					break;
				}
			}
		}

		else if (option == "ATAA")
		{
			printf("Input address you want to write to\n");
			while (1)
			{
				while (1)
				{
					std::cin >> temp;
					if ((temp > 65536) || (temp < 0))
					{
						printf("Incorrect address, try again (address larger than 65kb or lower than 0)\n");
						continue;
					}
					else
					{
						address = (addr)temp;
						break;
					}
				}
				printf("Input a value to write to an address\n");
				while (1)
				{
					std::cin >> temp;
					if ((temp > 256) || (temp < 0))
					{
						printf("Incorrect value, try again (address larger than 256 or lower than 0)\n");
						continue;
					}
					else
					{
						value = (addr)temp;
						break;
					}
				}
				printf("value %d was loaded into address %d\n", value, address);
				cpu.RAM.write(value, address);
				printf("Continue? (Y/N)\n");
				std::cin >> cont;
				if (cont == 'Y')
				{
					printf("Input next address\n");
					continue;
				}
				else
				{
					printf("\nInput memory load option\n");
					break;
				}
			}
		}

		else if (option == "LIST")
		{	
			addr val1;
			addr val2;

			printf("Input range of addresses to see listing\nInput first value (lower than last address)\n");
			while (1)
			{
				std::cin >> temp;
				if ((temp > 65536) || (temp < 0))
				{
					printf("Incorrect address range, try again (address larger than 65kb or lower than 0)\n");
					continue;
				}
				else
				{
					val1 = (addr)temp;
					break;
				}
			}
			printf("Input top value of range\n");
			while (1)
			{
				std::cin >> temp;
				if ((temp > 65536) || (temp < val1))
				{
					printf("Incorrect address range, try again (address larger than 65kb or lower than first value of range)\n");
					continue;
				}
				else
				{
					val2 = (addr)temp;
					break;
				}
			}
			for (addr i = val1; i < val2; i++)
			{
				printf("addr = %d, value = %d\n", i, cpu.RAM.read(i));
			}
			printf("\n Listing ended\n");

			printf("\nInput memory load option\n");
		}

		else if (option == "EXE")
		{
			while (1);
			{
				cpu.cycle(1);
			}
		}

		else if (option == "EXIT")
		{
			printf("Exiting emilator\nType any key to exit\n");
			getchar();
			getchar();
			exit(0);
			break;
		}

		else
		{
			printf("Incorrect option, try again\n");
			printf("Input option (type help to see all comands)\n");
		}
	}
}

