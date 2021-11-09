# Programming Assignment 4 - Eric Seals

Documentation for correctly using the exploit generator. There is one directory, named exploitWin, which contains the perl script.

# Exploiting the Winamp Bento skin

## Create the .maki file

There is only one file here, `win_amp.pl` which generates the `mcvcore.maki` file. 

On the Windows VM, place the perl script at the path `C:\Program Files\Winamp\Skins\Bento\scripts`. Open the Admin Shell to the same location and run the following to create the .maki file:

```bash
> perl win_amp.pl>mcvcore.maki
```

## Find Offset 

For this exploit to work correctly, it is necessary to exactly overwrite the SEH record words. 
This is done by first finding a value that is sufficiently large and overflows the stack / causes an exception to be raised - 20000 bytes is experimentally found to be large enough. 
With this, the metasploit tools are used to generate a pattern to find exactly the offset from the buffer to the SEH record. 

To generate the pattern, run the following on a Kali machine:
```bash
$ cd /usr/share/metasploit-framework/tools/exploit
$ ./pattern_create -l 20000
```

Use this pattern as the value for the string $function_name in the original perl script. 

Run Winamp and monitor with WinDBG. When you change the skin to Bento, an exception will be thrown. Run the following to see the values in the SEH record:

![Exchain_Windbg](res/Exchain_Windbg.png)

Use these values to find the offset, particularly it's the second value that matters. This is seen below, and the size 16756 is determined to be the exact offset from the start of the buffer to the start of the SEH record.

![Finding_the_offset](res/Finding_the_offset.png)

## Filling the two SEH record values

The first four bytes of the SEH record will simply be filled with a NOP NOP JMP 04. 
This way when the execution returns (described next), the code jumps to the shell code with is located after the SEH record.

The second four bytes of the SEH record is treated as a pointer to the exception handler implementation. 
Using both Gnarly in the WinDBG and the msfpescan on Kali, a location containing a POP POP RET instruction is found. 
Two pops is needed as it is found that the initial work Windows does, before the first SEH record is called, pushes two values on the stack, and they need to be cleared.  

This figure shows the output of the `!nmod` command from Gnarly. The .dll's to use for this exploit need to avoid the *ASLR protections.  
![nmod_for_winamp](res/nmod_for_winamp.png)

This figure shows the result of using msfpescan to find a code location 
![msfpescan_for_pop_pop_ret](res/msfpescan_for_pop_pop_ret.png)


```perl

```

```bash
$ cd /usr/share/metasploit-framework/tools/exploit
$ ./pattern_create.rb -l 5000
```

![Working_Exploit](res/Working_Exploit.png)
![Generating_Shellcode](res/Generating_Shellcode.png)

![Customizing_Payload](res/Customizing_Payload.png)



