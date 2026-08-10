#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct mem_address_list
{
    size_t len_B;
    bool is_it_free;
    struct mem_address_list *next;
} mem_address_list;

static mem_address_list *free_list_head = NULL;

extern char _end; // A statikus memory vége

static void* heap_ptr = NULL;
// static void* heap_end = NULL;

void init_heap(void)
{
    heap_ptr = &_end;
    //heap_end = 0x00100000 + (16 * 1024 * 1024);
    free_list_head = (mem_address_list *)&_end;
    free_list_head->next = NULL;
    free_list_head->is_it_free = true;
    free_list_head->len_B = 0;
}

void *kstack_alloc(int ptr_size_B)
{
    if (heap_ptr == NULL)
    {
        init_heap();
    }

    ptr_size_B = (ptr_size_B + 3) & ~ ((size_t)3);

    mem_address_list *current = free_list_head;

    while (current->next != NULL)
    {
        current = current->next;
    }
    
    mem_address_list *new_block;

    if (current->len_B == 0 && current == free_list_head)
    {
        new_block = current;
    }
    else
    {
        new_block = (mem_address_list *)((uint8_t *)current + sizeof(mem_address_list) + current->len_B);
        current->next = new_block;
    }

    new_block->len_B = ptr_size_B;
    new_block->is_it_free = false;
    new_block->next = NULL;

    return (void *)((uint8_t *)new_block + sizeof(mem_address_list));    
}

bool kfree(void *ptr)
{
    if (ptr == NULL || free_list_head == NULL)
    {
        return false;
    }

    mem_address_list *current = free_list_head;

    void *user_data_ptr = (void *)((uint8_t *)current + sizeof(mem_address_list));

    while (current != NULL)
    {
        if (ptr == user_data_ptr)
        {
            current->is_it_free = true;
            return true;
        }
        current = current->next;        
    }
   return false; 
}