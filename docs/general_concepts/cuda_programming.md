# Cuda Programming with C++

CUDA (Compute Unified Device Architecture) is a parallel computing platform and
application programming interface (API) model created by NVIDIA. It allows
software developers and software engineers to use a CUDA-enabled graphics
processing unit (GPU) for general purpose processing – an approach known as
GPGPU (General-Purpose computing on Graphics Processing Units). The goal of CUDA
is to provide a straightforward means of developing software that can take
advantage of the massive parallel computing power of GPUs to achieve dramatic
increases in computing performance.

### Languages Supported by CUDA

CUDA code is primarily written in:
- **CUDA C/C++**: An extended version of C/C++ with special constructs to
  exploit parallelism.
- **CUDA Fortran**: A version of Fortran with CUDA extensions designed for
  parallel processing.

Additionally, many other languages and APIs now support CUDA indirectly through
bindings or libraries, including Python (via libraries like PyCUDA), Java, and
more, enabling a wide range of developers to access CUDA's parallel computing
capabilities.

### How CUDA Works

CUDA works by allowing the developer to define C functions, called kernels,
which, when called, are executed N times in parallel by N different CUDA
threads, as opposed to only once like regular C functions. These threads are
organized into blocks and grids, which can be processed in parallel by the GPU.
This structure allows for efficient parallel computation of tasks that can be
divided into small, independent units of work.

### Command Line to Trigger CUDA Compilation

To compile CUDA code, you use the NVIDIA CUDA Compiler (nvcc), which is part of
the CUDA Toolkit. The command line might look something like this:

```sh
nvcc -o my_program my_program.cu
```

This command tells `nvcc` to compile the CUDA program `my_program.cu` and output
an executable named `my_program`.

### Managing Projects with CUDA

Managing a project with CUDA involves:
- Installing the CUDA Toolkit and ensuring your system's GPU drivers are up to
  date.
- Structuring your code to take advantage of parallelism, including memory
  management between the CPU and GPU.
- Using `nvcc` to compile your CUDA code.
- Debugging and profiling with tools like `cuda-gdb` and `nvprof` or the newer
  `nsight` systems and compute tools.

### Example: Matrix Multiplication using CUDA

Matrix multiplication is a common example to illustrate CUDA's parallel
computing capabilities. Here's a simplified version of what CUDA C/C++ code for
matrix multiplication might look like:

```cuda
__global__ void MatrixMulKernel(float* Md, float* Nd, float* Pd, int Width) {
    // Calculate the row index of the P element and Md
    int Row = blockIdx.y*blockDim.y+threadIdx.y;
    // Calculate the column index of P and Nd
    int Col = blockIdx.x*blockDim.x+threadIdx.x;

    if ((Row < Width) && (Col < Width)) {
        float Pvalue = 0;
        // Each thread computes one element of the block sub-matrix
        for (int k = 0; k < Width; ++k) {
            Pvalue += Md[Row*Width+k] * Nd[k*Width+Col];
        }
        Pd[Row*Width+Col] = Pvalue;
    }
}
```

This kernel function is designed to be run by multiple threads in parallel, with
each thread computing a single element of the result matrix. To use this kernel,
you'd allocate memory on the GPU, copy your input matrices to the GPU, execute
the kernel, and then copy the result matrix back to the CPU.

Remember, this is a simplified example. Practical use cases would need proper
memory management, error checking, and possibly tuning based on the specific
GPU's architecture.

## Matrix multiplication with CUDA

To perform matrix multiplication using CUDA on data from CSV files, you'll need to follow these general steps:

1. **Read the CSV files** into host memory (CPU).
2. **Allocate memory** on the GPU (device memory).
3. **Transfer the data** from the host to the GPU.
4. **Execute the matrix multiplication kernel** on the GPU.
5. **Transfer the result back** from the GPU to the host.
6. **Free the allocated memory** on the GPU.

Here's an outline of how you might accomplish this in CUDA, assuming you've
already implemented or obtained a CUDA kernel for matrix multiplication (like
the simplified version mentioned before) and have a method to read CSV files
into matrices in host memory:

### Step 1: Read CSV Files into Host Memory

You'll need a method to read the CSV files and store them in a suitable format
(e.g., arrays or vectors) in host memory. There are many libraries in various
languages that can help with reading CSV files. For simplicity, let's assume you
have two 2D arrays (or equivalent structures) holding your matrices from the CSV
files:

```c
float* matrixA; // Data from the first CSV
float* matrixB; // Data from the second CSV
```

### Step 2: Allocate Memory on the GPU

You use `cudaMalloc` to allocate memory on the GPU. For example, if you have two matrices of size `width x width`:

```c
float *d_matrixA, *d_matrixB, *d_matrixC;
size_t size = width * width * sizeof(float);
cudaMalloc(&d_matrixA, size);
cudaMalloc(&d_matrixB, size);
cudaMalloc(&d_matrixC, size); // For the result matrix
```

### Step 3: Transfer the Data from the Host to the GPU

Use `cudaMemcpy` to transfer the matrix data from host to device (GPU):

```c
cudaMemcpy(d_matrixA, matrixA, size, cudaMemcpyHostToDevice);
cudaMemcpy(d_matrixB, matrixB, size, cudaMemcpyHostToDevice);
```

### Step 4: Execute the Matrix Multiplication Kernel

Configure the kernel launch parameters (block size, grid size) and call the
matrix multiplication kernel. The configuration will depend on your specific
problem size and the GPU's architecture:

```c
dim3 threadsPerBlock(16, 16);
dim3 blocksPerGrid((width + threadsPerBlock.x - 1) / threadsPerBlock.x,
                   (width + threadsPerBlock.y - 1) / threadsPerBlock.y);
MatrixMulKernel<<<blocksPerGrid, threadsPerBlock>>>(d_matrixA, d_matrixB, d_matrixC, width);
```

### Step 5: Transfer the Result Back from the GPU to the Host

After the kernel execution completes, transfer the resulting matrix back to host memory:

```c
float* resultMatrix = (float*)malloc(size);
cudaMemcpy(resultMatrix, d_matrixC, size, cudaMemcpyDeviceToHost);
```

### Step 6: Free the Allocated Memory on the GPU

Don't forget to free the GPU memory
