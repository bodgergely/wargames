Rookies challange on pwnable.kr.

## Name

simple login

## Challenge

sudo apt-get install libssl-dev:i386

Can you get authentication from this server?

Download : http://pwnable.kr/bin/login

Running at : nc pwnable.kr 9003


## Analysis

The binary uses lots of OpenSSl library functions!
BIO
MD5

#include <openssl/md5.h>
vim /usr/include/openssl/md5.h

The scanf accepts a string length 30. 
Will overwrite the lowest byte of the next word on the stack (init func) 
with a zero in cae we supply string len >= 30.

### calcDecodeLength

last byte = len-1

Compares the (len-1) byte of our input with 0x3d.
Branches depending whether equal to it or not.

Compares the (len-2) byte of our input with 0x3d.
Branches depending whether equal to it or not.

Inserts two
0x8049048 <calcDecodeLength+63>     mov    dword ptr [ebp - 0xc], 2

Then some floating point ops:
0x804906a <calcDecodeLength+97>     fild   dword ptr [ebp - 0x10]

Algo:
f = float(len) * 0.75           // 22.5 = 30.0 * 0.75
f = f-2.0                       // 20.5

Save and the floating point control register then set a new value (0x0c7f)

Save the 'f' as in integer onto the stack by fistp instruction.

Restore the floating point control register by loading back the saved orig value.
(fldcw)

If the len of the input was 30 then the result of this function is 20 in eax.

### Base64Decode

We allocate with malloc 21 bytes. (20 + 1)

Then we fmemopen(input_string_mem_loc, len, 'r') which return a STREAM to our
input string.

We call BIO_f_base64() which returns us a BIO_METHOD pointer. Which is a method
to filter. This filter base64 encodes any data written through it and decodes any
data read through it. Type of the function is methods_b64.
Then we call BIO_new(BIO_method pointer) that returns a BIO pointer.

Then we call BIO_new_fp with the FILE argument we got from fmemopen.
That gets us a BIO pointer too.

We call BIO_push:
    - BIO_new returned BIO pointer
    - BIO_new_fp returned BIO pointer

BIO_push will append the second BIO arg to the first one and returns the first one.
We BIO_set_flags on the BIO with flag: 0x100

BIO_read:
    - BIO pointer
    - data: I think this is the malloced buffer to hold the decoded stuff
    - len: length of our input str to be decoded

After that the buffer holds the decoded stuff.

We terminate the decoded string with a ZERO byte.

We call BIO_free_all(BIO ptr)

We fclose the memstream.

If our decoded stream is longer than 12 bytes we fail with a "Wrong Length" message.

We copy from the decoded string to our 'input' mem area len bytes (determined by before)

We call:

**auth(len, decoded_msg)**

memcpy() the decoded string

#### calc_md5()

    - malloc 32 bytes
    - MD5_Init(,0x2,)
    - MD5_Update()
    - MD5_Final()

    - stringify the bytes

Print the stringified md5 hash

The program going to compare our hash string with the hash string:
"f87cd601aa7fedca99018a8be88eda34"

Also the first 4 bytes of the decoded base64 should be 0xdeadbeef

## Solution

The program has a bug! We can overwrite with the third dword with our 12 byte decoded
input one saved ebp! 
Our decoded input should be like: 0xdeadbeef 0xwhatever 0xstackaddrtoreturto

We should return to some memory value where the word next is the instruction somewhere in
function 'correct'. The only other place we can inject mem thourgh is thazt 30 bytes scanf in the
beginning. But not sure I knwo an exact address for that.
More likely we could scan the binary for an area where there is a word matching with the correct function's addr range.
 

0804925f <correct>:
 804925f:       55                      push   ebp
 8049260:       89 e5                   mov    ebp,esp
 8049262:       83 ec 28                sub    esp,0x28
 8049265:       c7 45 f4 40 eb 11 08    mov    DWORD PTR [ebp-0xc],0x811eb40
 804926c:       8b 45 f4                mov    eax,DWORD PTR [ebp-0xc]
 804926f:       8b 00                   mov    eax,DWORD PTR [eax]
 8049271:       3d ef be ad de          cmp    eax,0xdeadbeef
 8049276:       75 18                   jne    8049290 <correct+0x31>
 8049278:       c7 04 24 51 a6 0d 08    mov    DWORD PTR [esp],0x80da651
 804927f:       e8 4c 30 01 00          call   805c2d0 <_IO_puts>
 8049284:       c7 04 24 6f a6 0d 08    mov    DWORD PTR [esp],0x80da66f
 804928b:       e8 20 20 01 00          call   805b2b0 <__libc_system>
 8049290:       c7 04 24 00 00 00 00    mov    DWORD PTR [esp],0x0
 8049297:       e8 04 14 01 00          call   805a6a0 <exit>







