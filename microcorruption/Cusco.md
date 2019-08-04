Password:
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa2845


Buffer overflow happens, the password check fails, but since we overflowed the buffer, we overflowed a return address with
the known address to unlock_door(0x4528). 
