#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "address_book.h"

Status load_file(AddressBook *address_book)
{

	int ret = 0;
	int entries = 0;
	int column = 0;
	int currentEntry = 0;
	int phoneNumbers = 0;
	int emailAddresses = 0;
	int i;

	char c;
	char fileInput[32] = "";

	address_book->fp = fopen(DEFAULT_FILE, "r");

	if (address_book->fp == NULL)
	{

		ret = 1;

	}

	if (ret == 1)
	{

		printf("No address book exists yet. Creating a new one.\n");

		address_book->fp = fopen(DEFAULT_FILE, "wt+");
		
	}
	else{

		for (c = getc(address_book->fp); c != EOF; c = getc(address_book->fp)){

        	if (c == '\n'){

            	entries++;

			}
		
		}

		fclose(address_book->fp);

		address_book->fp = fopen(DEFAULT_FILE, "r");

		address_book->list = malloc(entries * sizeof(ContactInfo));

		for (c = getc(address_book->fp); c != EOF; c = getc(address_book->fp)){

			switch (column){

				case 0:
					switch (c){

						case ',':
								
							if (fileInput[0] != '\0'){

								currentEntry++;

								phoneNumbers = 0;

								emailAddresses = 0;

								address_book->list[currentEntry - 1].si_no = currentEntry;
								
								strcpy(address_book->list[currentEntry - 1].name[0], fileInput);
								
								strcpy(fileInput, "");

							}
							
							column++;
							break;

						default:
							strncat(fileInput, &c, 1);
							break;

					}

					break;
				
				case 1:
					switch (c){

						case ',':
							
							if (fileInput[0] != '\0'){
								
								phoneNumbers++;
								
								if (phoneNumbers <= 5){

									strcpy(address_book->list[currentEntry - 1].phone_numbers[phoneNumbers - 1], fileInput);	

								}

								strcpy(fileInput, "");

							}

							column++;
							break;

						default:
							strncat(fileInput, &c, 1);
							break;

					}

					break;

				case 2:
					switch (c){

						case '\n':
							if (fileInput[0] != '\0'){

								emailAddresses++;

								if (emailAddresses <= 5){

									strcpy(address_book->list[currentEntry - 1].email_addresses[emailAddresses - 1], fileInput);	

								}

								strcpy(fileInput, "");

							}

							column = 0;
							break;

						default:
							strncat(fileInput, &c, 1);
							break;

					}

				break;
			}

		}
        
	}

	fclose(address_book->fp);

	printf("Loaded address book successfully.\n");

	return e_success;
}

Status save_file(AddressBook *address_book)
{
	/*
	 * Write contacts back to file.
	 * Re write the complete file currently
	 */ 
	address_book->fp = fopen(DEFAULT_FILE, "w");

	if (address_book->fp == NULL)
	{
		return e_fail;
	}

	/* 
	 * Add the logic to save the file
	 * Make sure to do error handling
	 */ 

	fclose(address_book->fp);

	return e_success;
}
