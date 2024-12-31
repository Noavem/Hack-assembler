# Hack assembler
An assembler for the Hack assembly language[^1] written in C, utilizing a hash map implemented with [Pearson's hashing algorithm](https://dl.acm.org/doi/pdf/10.1145/78973.78978).

## How to run the assembler
Navigate to wherever you put the source files and enter the following command in your terminal to build the assembler executable:
```
make
```
To translate a ```.asm``` file into a ```.hack``` file, use the following command:
```
./main <filename.asm>
```
Where you replace <filename.asm> with the relevant assembly source file.
[^1]: As seen in *The Elements of Computing Systems*.
