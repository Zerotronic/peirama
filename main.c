/****************************************************************************
 * Copyright (c) 2016, Zerotronic                                           *
 * All rights reserved.                                                     *
 *                                                                          *
 * Redistribution and use in source and binary forms, with or without       *
 * modification, are permitted provided that the following conditions are   *
 * met:                                                                     *
 *                                                                          *
 * * Redistributions of source code must retain the above copyright notice, *
 *   this list of conditions and the following disclaimer.                  *
 *                                                                          *
 * * Redistributions in binary form must reproduce the above copyright      *
 *   notice, this list of conditions and the following disclaimer in the    *
 *   documentation and/or other materials provided with the distribution.   *
 *                                                                          *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS      *
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT        *
 * LIMITED TO,THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A   *
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT       *
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   *
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED *
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR   *
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF   *
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING     *
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS       *
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.             *
 *                                                                          *
 * File    : main.c                                                         *
 *                                                                          *
 * Purpose : Console mode (command line) program.                           *
 *                                                                          *
 * History : Date      Reason                                               *
 *           09/01/16  Created                                              *
 *                                                                          *
 ****************************************************************************/

// Includes
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

/****************************************************************************
 *                                                                          *
 * Function : current_date                                                  *
 *                                                                          *
 * Purpose  : Return Current Date.                                          *
 *                                                                          *
 * History  : Date      Reason                                              *
 *            09/01/16  Created                                             *
 *                                                                          *
 ****************************************************************************/

char* current_date(char* system_date_string)
{
	// Get system time
	time_t system_date = time(NULL);

	// Populate the tm struct
	struct tm* system_dt_struct = localtime(&system_date);

	// Extract data from tm struct and return data
	strftime(system_date_string, 10, "%Y/%m/%d", system_dt_struct);
	return system_date_string;
}

/****************************************************************************
 *                                                                          *
 * Function : current_time                                                  *
 *                                                                          *
 * Purpose  : Return Current Time.                                          *
 *                                                                          *
 * History  : Date      Reason                                              *
 *            09/01/16  Created                                             *
 *                                                                          *
 ****************************************************************************/

char* current_time(char* system_time_string)
{
	// Get system time
	time_t system_time = time(NULL);

	// Populate the tm struct
	struct tm* system_tm_struct = localtime(&system_time);

	// Extract data from tm struct and return data
	strftime(system_time_string, 5, "%H:%M", system_tm_struct);
	return system_time_string;
}

/****************************************************************************
 *                                                                          *
 * Function : IN                                                            *
 *                                                                          *
 * Purpose  : Write In time to file.                                        *
 *                                                                          *
 * History  : Date      Reason                                              *
 *            09/01/16  Created                                             *
 *                                                                          *
 ****************************************************************************/

void IN(char* txtfile)
{
	// Open file to append data
	FILE *f = fopen(txtfile, "a");
	if (f == NULL)
	{
    	printf("Error opening file!\n");
    	exit(1);
	}

	// Append data
	char* system_date_string = (char *)malloc(10 * sizeof(char));
	char* system_time_string = (char *)malloc(5 * sizeof(char));
	if (system_date_string != NULL)
		{
			if (system_time_string != NULL)
			{
				fprintf(f, "{'%s':['IN ','%s']}\n", current_date(system_date_string), current_time(system_time_string));
			} else {
				printf("No memory could be allocated for system_time_string!\n");
				exit(1);
			}
	} else {
		printf("No memory could be allocated for system_date_string!\n");
		exit(1);
	}
	free(system_date_string);
	free(system_time_string);

	// Close file
	fclose(f);
}

/****************************************************************************
 *                                                                          *
 * Function : OUT                                                           *
 *                                                                          *
 * Purpose  : Write Out time to file.                                       *
 *                                                                          *
 * History  : Date      Reason                                              *
 *            09/01/16  Created                                             *
 *                                                                          *
 ****************************************************************************/

void OUT(char* txtfile)
{
	// Open file to append data
	FILE *f = fopen(txtfile, "a");
	if (f == NULL)
	{
    	printf("Error opening file!\n");
    	exit(1);
	}

	// Append data
	char* system_date_string = (char *)malloc(10 * sizeof(char));
	char* system_time_string = (char *)malloc(5 * sizeof(char));
	if (system_date_string != NULL)
		{
			if (system_time_string != NULL)
			{
				fprintf(f, "{'%s':['OUT','%s']}\n", current_date(system_date_string), current_time(system_time_string));
			} else {
				printf("No memory could be allocated for system_time_string!\n");
				exit(1);
			}
	} else {
		printf("No memory could be allocated for system_date_string!\n");
		exit(1);
	}
	free(system_date_string);
	free(system_time_string);

	// Close file
	fclose(f);
}

/****************************************************************************
 *                                                                          *
 * Function : main                                                          *
 *                                                                          *
 * Purpose  : Main program function.                                        *
 *                                                                          *
 * History  : Date      Reason                                              *
 *            09/01/16  Created                                             *
 *                                                                          *
 ****************************************************************************/

int main(void)
{
    int state;

	printf ("Please enter 1 for IN or 2 for OUT: ");
	scanf ("%d", &state);

	if ( state == 1 ) {
		IN("/sdcard/Download/TIME.json");
	} else if ( state == 2 ) {
		OUT("/sdcard/Download/TIME.json");
	} else {
		printf ("!!Wrong Input!! Please enter 1 for IN or 2 for OUT");
	}

    return 0;
}

