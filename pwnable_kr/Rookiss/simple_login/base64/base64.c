#include <stdio.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/md5.h>

const char* input_base64 = "f87cd601aa7fedc";

typedef unsigned char u8;

void print_hex(const unsigned char* str)
{
    while(*str) {
        printf("\\x%x", *str);
        ++str;
    }
    printf("\n");
}

int Base64Decode(char* input, char* output)
{
    int read = -1;
    FILE* stream = fmemopen(input, strlen(input), "r");
    BIO* bio = BIO_new(BIO_f_base64());
    BIO* biofp = BIO_new_fp(stream, 0);
    biofp = BIO_push(bio, biofp);
    BIO_set_flags(biofp, 0x100);
    read = BIO_read(biofp, output, strlen(input));
    if (read == 0 || read == -1) {
        printf("BIO_read failed, read: %d\n", read);
    }
    BIO_free_all(biofp);
    fclose(stream);

    return read;  
}

int Base64Encode(char* input, char* output, int output_len)
{
    int written = -1;
    FILE* stream = fmemopen(output, output_len, "w");
    BIO* bio = BIO_new(BIO_f_base64());
    BIO* biofp = BIO_new_fp(stream, 0);
    biofp = BIO_push(bio, biofp);
    BIO_set_flags(biofp, 0x100);
    written = BIO_write(biofp, input, strlen(input));
    if (written == 0 || written == -1) {
        printf("BIO_write failed, written: %d\n", written);
    }
    BIO_free_all(biofp);
    fclose(stream);

    return written;  

}

void test_decode(char* encoded, char* expected)
{
    char buff[64] = {0};
    int len = -1;
    printf("Decoding:%s\n", encoded);
    len = Base64Decode(encoded, buff);
    if(strcmp(buff, expected)!=0) {
        printf("Decoded:");
        print_hex(buff);
        printf("Expected:");
        print_hex(expected);
        //printf("Decoded to:%s,len: %d but expected:%s\n", buff, len, expected);
    }
}

// MD5 is a crypto hash function with a 128 bit output
/**
hash: allocated by caller, 33 bytes, first 32 bytes will be filled by the function
and the 33th byte should be set to NULL by the caller. Each 2 bytes represent
the textual hex value of a byte.
   */
void hex_string_md5(u8* hash, const u8* md)
{
    int i = 0;
    u8* p = hash;
    for(i=0;i<16;i++) {
        snprintf(p, 32, "%02x", md[i]);
        p+=2;
    }
}

// md should be allocated by caller, should be 16 bytes long
void calc_md5(u8* md, const u8* data, int len)
{
    MD5_CTX md5ctx;
    
    MD5_Init(&md5ctx);
    while(1) {
        if(len <=0) {
            MD5_Final(md, &md5ctx);
            break;
        }

        if(len < 0x200) {
            MD5_Update(&md5ctx, data, len);
        }
        else {
            MD5_Update(&md5ctx, data, 0x200);
        }
        len-=0x200;
        data+=0x200;
    }
}

/*
   Our base64 should start with '776t3'
   */
void validate_deadbeef(const u8* input)
{
    if(*(unsigned int*)input != 0xdeadbeef) {
        printf("Base64 decode did not result in 0xdeadbeef start!\n");
        exit(1);
    }
}

void print_md5(u8* md)
{
    int i=0;
    unsigned int* p = (unsigned int*)md;
    printf("md5: ");
    for(i=0;i<4;i++) {
        printf("%04x ", *p);
        p++;
    }
    printf("\n");
}

u8* md5(u8* base64)
{
    u8 decoded[32] = {0};
    u8 md[16] = {0};
    u8 hash[33] = {0};
    u8* ret;
    Base64Decode(base64, decoded);
    printf("decoded len: %d\n", strlen(decoded));
    validate_deadbeef(decoded);
    calc_md5(md, decoded, strlen(decoded));
    print_md5(md);
    hex_string_md5(hash,md);
    ret = malloc(sizeof(hash));
    memcpy(ret, hash, sizeof(hash));
    return ret;
}


/*
   We need a string that result after base64 decode in an input len of 12 bytes.
   The decoded stuff also has to start with 0xdeadbeef.
   To get a 12 bytes input the base64 input has to be at least len 16 and max 17.
*/

int main(int argc, char* argv[])
{
    int a;
    printf("Stack: %p\n", &a);
    printf("Hash:%s\n", md5(argv[1]));
    return 0;
}

