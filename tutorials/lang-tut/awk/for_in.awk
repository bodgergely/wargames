BEGIN {
    arr[0] = 6;
    arr[1] = 4;
    arr[3] = 9;
    arr[12345] = 13;

    for (i in arr) {
       printf "arr[%d] = %d\n", i, arr[i]; 
    }
    
}
