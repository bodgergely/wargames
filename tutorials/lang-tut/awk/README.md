

# Examples

awk 'BEGIN {printf "Sr No\tName\tSub\tMarks\n"} {print}' marks.txt
awk '{print}' ./marks.txt
awk -f command.awk marks.txt

### Assign variable:

awk -v name=Jerry 'BEGIN{printf "Name = %s\n", name}'

### Dump global variables

awk --dump-variables ''
Now we the vars saved to awkvars.out

### Lint

awk --lint '' /bin/ls


### Profiling

awk --profile 'BEGIN{printf"---|Header|--\n"} {print} END{printf"---|Footer|---\n"}' marks.txt > /dev/null ./marks.txt

Profile info gets saved to awkprof.out


## Printing columns
$0 means the whole line
awk '{print $3 "\t" $4}' marks.txt


## Pattern matching

awk '/Physics/ {print $4 "\t" $3}' marks.txt

### Counting the matches

It will count any line that contains an 'a':
awk '/a/{++cnt} END {print "Count = ", cnt}' marks.txt

awk 'BEGIN {cnt=0} /a/{++cnt} {print "Count = ", cnt}' marks.txt

### Counting

Use length to count and match when true
awk 'length($0) > 18' marks.txt
awk 'length($2) > 4' marks.txt

## ARGV, ARGV

Like in C, we can 
awk 'BEGIN {print "Arguments =", ARGV[0]}' marks.txt
awk 'BEGIN {print "Arguments =", ARGV[1]}' marks.txt

## CONVFMT

awk 'BEGIN { print "Conversion Format =", CONVFMT }'

## Loops

BEGIN { 
   for (i = 0; i < ARGC; ++i) { 
      printf "ARGV[%d] = %s\n", i, ARGV[i] 
   } 
}

awk 'BEGIN {arr[0] = 1; arr[1] = 2; arr[2] = 3; for (i in arr) printf "arr[%d] = %d\n", i, arr[i]}'

## ENVIRON

awk 'BEGIN { print ENVIRON["USER"] }'

## FS - field separator

Use the -F flag to change, by default space(' ')

## NF - number of fields in the current record

Print only the records that have fields more than 2!
echo -e "One Two\nOne Two Three\nOne Two Three Four" | awk 'NF > 2'

## NR - current record number - index starts from 1

echo -e "One Two\nOne Two Three\nOne Two Three Four" | awk 'NR < 3'

## match

Print the line if the second field is Rahul
awk '{if(match($2, "Rahul")) print $0}' ./marks.txt


## Regex

Operators: ~, !~

Look in the row for the pattern "ar"
awk '$0 ~ "ar"' marks.txt

Do mnot macth the pattern:
awk '$0 !~ "[eE]ng"' marks.txt

The other for is /pattern/

awk '/Maths/' marks.txt

Start of line: (^)
echo -e "This\nThat\nThere\nTheir\nthese" | awk '/^The/'

End of line: ($)

echo -e "This\nThat\nThere\nTheir\nthese" | awk '/ese$/'










# Links

https://www.tutorialspoint.com/awk/awk_workflow.htm
