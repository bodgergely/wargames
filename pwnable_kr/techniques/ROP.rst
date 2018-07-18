Return-oriented programming (ROP)
=================================

https://www.trustwave.com/Resources/SpiderLabs-Blog/Linux-Kernel-ROP---Ropping-your-way-to---(Part-1)/

https://en.wikipedia.org/wiki/Return-oriented_programming

ROPGadget tool
--------------

This tool lets you search your gadgets on your binaries to facilitate your ROP exploitation. 

https://github.com/JonathanSalwan/ROPgadget.git


Definition:
----------

In this technique, an attacker gains control of the call stack to hijack program control flow and then executes carefully chosen machine instruction sequences that are already present in the machine's memory, called "gadgets".



Each gadget typically ends in a return instruction and is located in a subroutine within the existing program and/or shared library code. Chained together, these gadgets allow an attacker to perform arbitrary operations on a machine employing defenses that thwart simpler attacks.



Return-oriented programming is an *advanced* version of a *stack smashing attack*.

Stack smashing attack: 
----------------------

In a standard buffer overrun attack, the attacker would simply write attack code (the "payload") onto the stack and then overwrite the return address with the location of these newly written instructions. Nowadays most OSes have protection (randomized stack address space, non executable stack). 
Hardware support is also present to refuse code execution on user writable area.

A clever new approach is ROP where we use code fragments that are already present in memory so no need for code injection. Return address manipulation is needed to jump to the subsequent gadgets.
A typical data execution prevention cannot defend against this attack because the adversary did not use malicious code but rather combined "good" instructions by changing return addresses; therefore the code used would not be marked non-executable.

Return-into-libc technique (ret2libc)
--------------------------

In a return-into-library attack, an attacker hijacks program control flow by exploiting a buffer overrun vulnerability. The attacker instead chooses an available library function and overwrites the return address with its entry location. Further stack locations are then overwritten, obeying applicable calling conventions, to carefully pass the proper parameters to the function so it performs functionality useful to the attacker.

Can be extended to unlimited chaining of function calls.

But this technique is not effective nowadays on x64 processors! On x64 we pass the function args in the registers not on the stack so we need to put those args into the registers somehow... 
See below how.

Borrowed code chunks
--------------------

This technique looks for functions that contain instruction sequences that pop values from the stack into registers. Careful selection of these code sequences allows an attacker to put suitable values into the proper registers to perform a function call under the new calling convention. The rest of the attack proceeds as a return-into-library attack.









