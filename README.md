# Memory Management Unit (MMU) Simulator

## Description
The Memory Management Unit (MMU) Simulator project aims to create a software tool that models the behavior of an MMU, enabling experimentation with virtual memory management techniques. The MMU is a crucial component of modern computer systems responsible for translating virtual addresses into physical addresses and managing memory access.

## Background Concepts
### Virtual Memory, MMU, and Paging
- **Virtual Memory**: Virtual memory is a memory management technique that provides an abstraction of the computer's physical memory into a larger, contiguous address space.
- **Memory Management Unit (MMU)**: The MMU is hardware or software that translates virtual addresses into physical addresses, facilitating memory access and management.
- **Paging**: Paging is a memory management scheme used by MMUs to divide physical memory into fixed-size blocks called pages, corresponding to equally sized blocks in the virtual address space.

### Memory Management Policies and Page Replacement Algorithms
- **Memory Management Policies**: Memory management policies dictate how the MMU handles memory allocation, deallocation, and access. These policies include page replacement algorithms, allocation strategies, and memory access permissions.
- **Page Replacement Algorithms**: Page replacement algorithms determine which page to evict from physical memory when it is full and a new page needs to be loaded. Common algorithms include FIFO (First-In, First-Out), LRU (Least Recently Used), and optimal.

### Weakly Ordered Memory Models
- **Weakly Ordered Memory Models**: Weakly ordered memory models define the ordering constraints on memory operations in a parallel computing environment. Understanding these models is crucial for ensuring correct behavior in multi-core and parallel systems.

## Skills Utilized
- Understanding of virtual memory, MMU, and paging.
- Knowledge of memory management policies and weakly ordered memory models.
- Proficiency in C for developing the simulator.
- Python for creating a user-friendly interface and scripting tests.

## Key Components
1. **Simulation of Address Translation**: The simulator translates virtual addresses to physical addresses using the implemented MMU logic, simulating the behavior of a real MMU.
2. **Page Replacement Algorithms**: Various page replacement algorithms are implemented to simulate different memory management policies and strategies.
3. **Visualization Tools**: Tools are provided to visualize memory access patterns and performance metrics, aiding in understanding and analysis.
4. **User Interface**: A user-friendly interface is developed using Python to configure and run simulations, enabling easy experimentation with different parameters and settings.

## Running the Simulation

To run the MMU simulator:

1. Clone the repository to your local machine:

   ```bash
   git clone https://github.com/example/mmu-simulator.git
   ```

2. Navigate to the project directory:

   ```bash
   cd mmu-simulator
   ```

3. Open the `main.c` file and modify the `simulate_mmu` function to specify the desired replacement strategy (FIFO or LRU).

4. Compile the source code:

   ```bash
   gcc -o mmu_simulator main.c
   ```

5. Run the executable:

   ```bash
   ./mmu_simulator
   ```

## Contributors
- Rutuja Muttha
(rmuttha@pdx.edu)

