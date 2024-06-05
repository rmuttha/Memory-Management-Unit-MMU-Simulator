# Author: Rutuja Muttha

import random

def fifo_access(replacement_strategy, page_number):
    fifo = replacement_strategy
    for i in range(fifo['size']):
        if fifo['queue'][i] == page_number:
            return
    if fifo['size'] == NUM_FRAMES:
        fifo['queue'][fifo['head']] = page_number
        fifo['head'] = (fifo['head'] + 1) % NUM_FRAMES
    else:
        fifo['queue'][fifo['size']] = page_number
        fifo['size'] += 1

def lru_access(replacement_strategy, page_number):
    lru = replacement_strategy
    for i in range(lru['size']):
        if lru['pages'][i] == page_number:
            for j in range(i, lru['size'] - 1):
                lru['pages'][j] = lru['pages'][j + 1]
            lru['pages'][lru['size'] - 1] = page_number
            return
    if lru['size'] == NUM_FRAMES:
        for i in range(lru['size'] - 1):
            lru['pages'][i] = lru['pages'][i + 1]
        lru['pages'][lru['size'] - 1] = page_number
    else:
        lru['pages'][lru['size']] = page_number
        lru['size'] += 1

def handle_page_fault(mmu, page_number):
    if mmu['num_free_frames'] == 0:
        evicted_page = mmu['replacement_strategy'](mmu['replacement_strategy'], 0)
        frame_number = mmu['page_table']['entries'][evicted_page]
        mmu['page_table']['entries'][evicted_page] = 0
        mmu['frame_table'][frame_number] = 0
        mmu['free_frames'][mmu['num_free_frames']] = frame_number
        mmu['num_free_frames'] += 1
    frame_number = mmu['free_frames'][mmu['num_free_frames'] - 1]
    mmu['page_table']['entries'][page_number] = frame_number
    mmu['frame_table'][frame_number] = page_number
    mmu['replacement_access'](mmu['replacement_strategy'], page_number)
    mmu['page_faults'] += 1

def translate_address(mmu, virtual_address):
    page_number = virtual_address // PAGE_SIZE
    if mmu['page_table']['entries'][page_number] == 0:
        handle_page_fault(mmu, page_number)
    frame_number = mmu['page_table']['entries'][page_number]
    offset = virtual_address % PAGE_SIZE
    return frame_number * PAGE_SIZE + offset

def simulate_mmu(mmu):
    # Simulate a series of address translations
    for i in range(20):
        virtual_address = random.randint(0, NUM_PAGES * PAGE_SIZE - 1)
        physical_address = translate_address(mmu, virtual_address)
        print(f"Virtual address: {virtual_address:#010x} -> Physical address: {physical_address:#010x}")
    print(f"Total page faults: {mmu['page_faults']}")

def main():
    page_table = {'entries': [0] * NUM_PAGES}
    frame_table = [0] * NUM_FRAMES
    free_frames = list(range(NUM_FRAMES))

    fifo_strategy = {'queue': [0] * NUM_FRAMES, 'size': 0, 'head': 0}
    lru_strategy = {'pages': [0] * NUM_FRAMES, 'size': 0}

    mmu1 = {'page_table': page_table, 'frame_table': frame_table, 'free_frames': free_frames, 'num_free_frames': NUM_FRAMES, 'page_faults': 0, 'replacement_strategy': fifo_access, 'replacement_access': fifo_access, 'replacement_strategy': fifo_strategy}
    mmu2 = {'page_table': page_table, 'frame_table': frame_table, 'free_frames': free_frames, 'num_free_frames': NUM_FRAMES, 'page_faults': 0, 'replacement_strategy': lru_access, 'replacement_access': lru_access, 'replacement_strategy': lru_strategy}

    print("Simulating with FIFO replacement strategy:")
    simulate_mmu(mmu1)

    print("\nSimulating with LRU replacement strategy:")
    simulate_mmu(mmu2)

if __name__ == "__main__":
    main()
