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
 ****************************************************************************/

// Includes
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Declare new struct to hold values
typedef struct dt
{
    char *sdate;
    char *stime;
}DTS;

// Function to clear memory of DTS
void DestroyDTS(DTS *x)
{
    free(x->sdate);
    free(x->stime);
}

// Function to create a DTS struct
DTS CreateDTS(size_t dsz, size_t tsz)
{
    // Try to allocate DTS structure.
    DTS *retVal = malloc (sizeof(DTS));
    if (retVal == NULL)
    { 
        printf("struct memory allocation failed.\n"); 
        exit(1);
    }
    // Try to allocate DTS data, free structure if fail.
    retVal->sdate = malloc (dsz);
    retVal->stime = malloc (tsz);
    if (retVal->sdate == NULL) {
        free (retVal);
        printf("sdate memory allocation failed.\n"); 
        exit(1);
    }
    if (retVal->stime == NULL) {
        free (retVal);
        printf("stime memory allocation failed.\n"); 
        exit(1);
    }
    return *retVal;
}

// Function to write data to file
void dt_write(char* txtfile)
{
    // Get system date and time
	time_t system_date = time(NULL);
	// Construct the tm struct
	struct tm *system_date_struct = localtime(&system_date);
	
	// Find out sizes for date and time DTS elements
    size_t sdatesz = sizeof(system_date_struct->tm_year) + sizeof(system_date_struct->tm_mon) + sizeof(system_date_struct->tm_mday) + 2 * sizeof(char);
    size_t stimesz = sizeof(system_date_struct->tm_hour) + sizeof(system_date_struct->tm_min) + sizeof(char);
    // Create a DTS struct
    DTS pdt_str = CreateDTS(sdatesz, stimesz);
    // Populate elements of DTS struct with date amd time
	strftime(pdt_str.sdate, sdatesz, "%Y/%m/%d", system_date_struct);
	strftime(pdt_str.stime, stimesz, "%H:%M", system_date_struct);
	
	// Open file to append data
	FILE *f = fopen(txtfile, "a");
	if (f == NULL)
	{
    	printf("Error opening file!\n");
    	exit(1);
	}
	
	// append data
	fprintf(f, "{'%s':['OUT','%s']}\n", pdt_str.sdate, pdt_str.stime);
	
	// Close file
	fclose(f);
	
	// Free memory
	DestroyDTS(&pdt_str);
}

int main(void)
{
	dt_write("TIME.json");
}
