// Author: Rutuja Muttha

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define PAGE_SIZE 4096  // 4 KB
#define NUM_FRAMES 4
#define NUM_PAGES 10

typedef struct PageTable {
    uint32_t entries[NUM_PAGES];
} PageTable;

typedef struct FIFOReplacement {
    uint32_t queue[NUM_FRAMES];
    uint32_t size;
    uint32_t head;
    uint32_t tail;
} FIFOReplacement;

typedef struct LRUReplacement {
    uint32_t pages[NUM_FRAMES];
    uint32_t size;
} LRUReplacement;

typedef struct MMU {
    PageTable page_table;
    uint32_t frame_table[NUM_FRAMES];
    uint32_t free_frames[NUM_FRAMES];
    uint32_t num_free_frames;
    uint32_t page_faults;
    void (*replacement_access)(void*, uint32_t);
    void* replacement_strategy;
} MMU;

void fifo_access(void* replacement_strategy, uint32_t page_number) {
    FIFOReplacement* fifo = (FIFOReplacement*)replacement_strategy;
    for (uint32_t i = 0; i < fifo->size; i++) {
        if (fifo->queue[i] == page_number) {
            return;
        }
    }
    if (fifo->size == NUM_FRAMES) {
        fifo->queue[fifo->head] = page_number;
        fifo->head = (fifo->head + 1) % NUM_FRAMES;
    } else {
        fifo->queue[fifo->size++] = page_number;
    }
}

void lru_access(void* replacement_strategy, uint32_t page_number) {
    LRUReplacement* lru = (LRUReplacement*)replacement_strategy;
    for (uint32_t i = 0; i < lru->size; i++) {
        if (lru->pages[i] == page_number) {
            for (uint32_t j = i; j < lru->size - 1; j++) {
                lru->pages[j] = lru->pages[j + 1];
            }
            lru->pages[lru->size - 1] = page_number;
            return;
        }
    }
    if (lru->size == NUM_FRAMES) {
        for (uint32_t i = 0; i < lru->size - 1; i++) {
            lru->pages[i] = lru->pages[i + 1];
        }
        lru->pages[lru->size - 1] = page_number;
    } else {
        lru->pages[lru->size++] = page_number;
    }
}

void handle_page_fault(MMU* mmu, uint32_t page_number) {
    if (mmu->num_free_frames == 0) {
        uint32_t evicted_page = mmu->replacement_strategy == fifo_access ? mmu->replacement_strategy(mmu->replacement_strategy, 0) : mmu->replacement_strategy(mmu->replacement_strategy, 0);
        uint32_t frame_number = mmu->page_table.entries[evicted_page];
        mmu->page_table.entries[evicted_page] = 0;
        mmu->frame_table[frame_number] = 0;
        mmu->free_frames[mmu->num_free_frames++] = frame_number;
    }
    uint32_t frame_number = mmu->free_frames[--mmu->num_free_frames];
    mmu->page_table.entries[page_number] = frame_number;
    mmu->frame_table[frame_number] = page_number;
    mmu->replacement_access(mmu->replacement_strategy, page_number);
    mmu->page_faults++;
}

uint32_t translate_address(MMU* mmu, uint32_t virtual_address) {
    uint32_t page_number = virtual_address / PAGE_SIZE;
    if (mmu->page_table.entries[page_number] == 0) {
        handle_page_fault(mmu, page_number);
    }
    uint32_t frame_number = mmu->page_table.entries[page_number];
    uint32_t offset = virtual_address % PAGE_SIZE;
    return frame_number * PAGE_SIZE + offset;
}

void simulate_mmu(MMU* mmu) {
    // Simulate a series of address translations
    for (uint32_t i = 0; i < 20; i++) {
        uint32_t virtual_address = rand() % (NUM_PAGES * PAGE_SIZE);
        uint32_t physical_address = translate_address(mmu, virtual_address);
        printf("Virtual address: %#010x -> Physical address: %#010x\n", virtual_address, physical_address);
    }
    printf("Total page faults: %u\n", mmu->page_faults);
}

int main() {
    PageTable page_table = {0};
    uint32_t frame_table[NUM_FRAMES] = {0};
    uint32_t free_frames[NUM_FRAMES] = {0};
    uint32_t num_free_frames = NUM_FRAMES;
    
    FIFOReplacement fifo_strategy = {{0}, 0, 0, 0};
    LRUReplacement lru_strategy = {{0}, 0};

    MMU mmu1 = {page_table, frame_table, free_frames, num_free_frames, 0, fifo_access, &fifo_strategy};
    MMU mmu2 = {page_table, frame_table, free_frames, num_free_frames, 0, lru_access, &lru_strategy};

    printf("Simulating with FIFO replacement strategy:\n");
    simulate_mmu(&mmu1);

    printf("\nSimulating with LRU replacement strategy:\n");
    simulate_mmu(&mmu2);

    return 0;
}
