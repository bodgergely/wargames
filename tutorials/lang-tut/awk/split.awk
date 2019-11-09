BEGIN {
   str = "One,Two,Three,Four"
   split(str, arr, ",")
   print "Array contains following values"
   
   for (i in arr) {
      print i, arr[i]
   }
}
