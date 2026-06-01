#include <stdio.h>
#include <stdlib.h>

int main(int argument_count, char *argument_vector[])
{

    int total_virtual_memory_in_mb, single_page_size_in_kb;
    unsigned int input_virtual_address;

    unsigned int total_virtual_memory_in_bytes;
    unsigned int single_page_size_in_bytes;
    unsigned int total_pages_in_system;

    unsigned int calculated_page_number, calculated_offset;
    unsigned int *hardware_page_table;

    // Check correct arguments (Program name + 3 inputs)
    if (argument_count != 4)
    {
        printf("Usage: %s <VirtualSpace_MB> <PageSize_KB> <VirtualAddress>\n", argument_vector[0]);
        return 1;
    }

    // Convert command-line text inputs to numbers
    total_virtual_memory_mb = atoi(argument_vector[1]);
    single_page_size_kb = atoi(argument_vector[2]);
    input_virtual_address = atoi(argument_vector[3]);

    // Convert megabytes and kilobytes completely to bytes
    total_virtual_memory_bytes = total_virtual_memory_mb * 1024 * 1024;
    single_page_size_bytes = single_page_size_kb * 1024;

    // Boundary check: ensure target address falls inside allocated virtual memory
    if (input_virtual_address >= total_virtual_memory_bytes)
    {
        printf("Invalid Virtual Address\n");
        return 1;
    }

    // Calculate total slots needed in the page table array
    total_pages_in_system = total_virtual_memory_bytes / single_page_size_bytes;

    // Dynamically allocate memory for our page table array on the heap
    hardware_page_table = (unsigned int *)malloc(total_pages_in_system * sizeof(unsigned int));
    if (hardware_page_table == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Identity mapping setup: map page index i directly to physical frame index i
    for (unsigned int page_index = 0; page_index < total_pages_in_system; page_index++)
    {
        hardware_page_table[page_index] = page_index;
    }

    // Perform Address Translation math
    calculated_page_number = input_virtual_address / single_page_size_bytes;
    calculated_offset = input_virtual_address % single_page_size_bytes;

    // Verify page number falls inside table boundaries and print output
    if (calculated_page_number >= total_pages_in_system)
    {
        printf("Page Table Miss!\n");
    }
    else
    {
        printf("\n--- Address Translation ---\n");
        printf("Virtual Address: %u\n", input_virtual_address);
        printf("Page Number    : %u\n", calculated_page_number);
        printf("Offset         : %u\n", calculated_offset);
        printf("Physical Addr  : <%u, %u>\n",
               hardware_page_table[calculated_page_number], calculated_offset);
    }

    // Free dynamically allocated heap RAM to prevent memory leaks
    free(hardware_page_table);

    return 0;
}