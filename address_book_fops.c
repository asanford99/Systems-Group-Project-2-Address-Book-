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
	int indexCount = 0;
	int entries = 0;
	int column = 0;
	int i;
	int j;

	char c;
	char indexCheck[32] = "";
	char fileInput[32] = "";
	char line[132];
	char *token;

	address_book->list = (ContactInfo*)malloc(sizeof(ContactInfo));

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

		printf("Loaded address book successfully.\n");

		for (c = getc(address_book->fp); c != EOF; c = getc(address_book->fp)){

			printf("%c", c);

			switch (column){

				case 0:
					switch (c){

						case ',':

							if (strcmp(fileInput, "")){

								entries++;

								address_book->count = entries;

								address_book->list = (ContactInfo*)realloc(address_book->list, entries * sizeof(ContactInfo));

								address_book->list[entries - 1].si_no = entries;

								strcpy(address_book->list[entries - 1].name[0], fileInput);

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

							if (strcmp(fileInput, "")){

								indexCount = 0;

								strcpy(indexCheck, "not null");

								for (i = 0; (i < 5) || !strcmp(indexCheck, ""); i++){

									indexCount++;

									strcpy(indexCheck, address_book->list[entries-1].phone_numbers[i]);

								}

								if (indexCount < 5){

									strcpy(address_book->list[entries - 1].phone_numbers[indexCount], fileInput);	

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
							if (strcmp(fileInput, "")){

								indexCount = 0;

								strcpy(indexCheck, "not null");

								for (i = 0; (i < 5) || !strcmp(indexCheck, ""); i++){

									indexCount++;

									strcpy(indexCheck, address_book->list[entries-1].email_addresses[i]);

								}

								if (indexCount < 5){

									strcpy(address_book->list[entries - 1].email_addresses[indexCount], fileInput);	

								}

								strcpy(fileInput, "");

							}

							printf("%s %s %s %d", address_book->list[0].name[0], address_book->list[0].phone_numbers[0], address_book->list[0].email_addresses[0], address_book->list[0].si_no);

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

	printf("%d", entries);

	fclose(address_book->fp);

	for (i = 0; i < entries; i++){

		printf("Contact %d\n", (i + 1));

		printf("Name: %s\n", address_book->list[i].name[0]);

		printf("S Number: %d\n", address_book->list[i].si_no);

		printf("Phone Number(s): ");

		for (j = 0; j < 5 || !strcmp(address_book->list[i].phone_numbers[j], ""); j++){

			printf("%s ", address_book->list[i].phone_numbers[j]);

		}

		printf ("\nEmail Address('): ");

		for (j = 0; j < 5 || !strcmp(address_book->list[i].email_addresses[j], ""); j++){

			printf("%s ", address_book->list[i].email_addresses[j]);

		}

		printf("\n");

	}

	return e_fail;
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
