BEGIN { 
   for (i = 0; i < ARGC; ++i) { 
      printf "ARGV[%d] = %s\n", i, ARGV[i] 
   } 
}

{printf $1 "\t" $2 "\n"}

END{
    for (i = 0; i < 5; ++i) {
       print "Helloo" 
    }
    
}
