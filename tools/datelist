#!/bin/bash -e
#
# Datelist_v0.7 by TAPE
# (C)opyright 2012
# Last edited dd 24-06-2012 16:00
#
#Fixed settings 
REDBOLD=$(tput setaf 1 && tput bold)	# Bold red fonts
GREENBOLD=$(tput setaf 2 && tput bold)	# Bold green fonts
BLUEBOLD=$(tput setaf 6 && tput bold)	# Bold blue fonts
STAND=$(tput sgr 0)			# Standard fonts


function version () {
clear
echo $BLUEBOLD"TAPE's_       _        _ _     _
     | |     | |      | (_)   | |  
   __| | __ _| |_  ___| |_ ___| |_ 
  / _  |/ _  | __|/ _ \ | / __| __|
 | (_| | (_| | |_ | __/ | \__ \ |_ 
  \____|\____|\__|\___|_|_|___/\__|
v0.7$STAND"
echo
echo
echo $GREENBOLD"---~~~===///\\\\\===~~~---"
echo $REDBOLD"  datelist Version 0.7$STAND"
echo $BLUEBOLD"       June 2012"$STAND
echo $GREENBOLD"---~~~===\\\\\///===~~~---"
echo
echo
echo  -ne $STAND"Hit enter to continue "
read go_info
if [ "$go_info" == "" ] ; then

echo "
('q' to quit)

datelist v0.7
24-06-2012


PURPOSE
=======
To quickly ( now it IS relatively quick ;) ) create a list of a range of dates for use in for 
instance password lists to test for possible weak password use.
As from version 0.5, datelist no longer uses the linux 'date' command, but is based on simple 
listing and calculations, this has the benefit that it is much faster and no longer limited 
to dates between 1902 -- 2037.


DEPENDANCIES
============
This script is written to be used on the linux distro BackTrack and has not been tested on 
any other (linux) distro.


USAGE
=====
Creating a date wordlist
------------------------
To creating a date wordlist with datelist, you must enter 4 options;
-b  beginning date
-e  ending date
-f  format of output
-o  output filename
example;
./datelist -b 1999-01-01 -e 1999-01-31 -f ddmmyy -o dates.txt

The dates entered as beginning and ending date MUST be in the
format 'yyyy-mm-dd' to allow the program to work correctly.

The format for the output can ONLY be one of the below;
ddmmyy
ddmmyyyy
mmddyy
mmddyyyy
yymmdd
yyyymmdd

The output filename can be whatever you like, datelist will also
warn you if you are about to overwrite an existing file and allow
you to cancel.


Appending word/characters with -a switch
----------------------------------------
Since 0.7 you can specify to append a word/characters directly with
the command to create the datelist with the -a switch. 

example;
./datelist -b 1999-01-01 -e 1999-01-31 -f mmddyyyy -o dates.txt -s - -a TEST
--> 01-01-1999TEST -- 31-01-1999TEST

Prepending word/characters with -p switch
-----------------------------------------
Since 0.7 you can specify to prepend a word/characters directly with
the command to create the datelist with the -p switch. 

example;
./datelist -b 1999-01-01 -e 1999-01-31 -f mmddyyyy -o dates.txt -s - -p TEST
--> TEST01-01-1999 -- TEST31-01-1999

Using the -s switch to include spacing characters
-------------------------------------------------
By including the -s switch, you tell datelist to include
a spacing character between the days, months and years.
(this will work regardless of the output format you choose to use)

The spacing character can almost be whatever you like, however
certain characters will require escaping (with backslash \).
Exception is forward slash, I hardcoded that one in to work without
escaping as it is a commonly used spacing character in dates.

examples;
./datelist -b 1999-01-01 -e 1999-01-31 -f ddmmyy -o dates.txt -s .
./datelist -b 1999-01-01 -e 1999-01-31 -f ddmmyyyy -o dates.txt -s /
./datelist -b 1999-01-01 -e 1999-01-31 -f yymmdd -o dates.txt -s -
./datelist -b 1999-01-01 -e 1999-01-31 -f yyyymmdd -o dates.txt -s \|
./datelist -b 1999-01-01 -e 1999-01-31 -f mmddyy -o dates.txt -s \~
./datelist -b 1999-01-01 -e 1999-01-31 -f mmddyyyy -o dates.txt -s \*

datelist will then create the wordlist with the spacing character included.


Appending numeric values to the beginning of an existing
(date)wordlist with the -A switch
---------------------------------------------------------
I did not manage to get this function working nicely from the command
line within datelist as I had hoped.
So in order to append numeric values, you need to start datelist as follows;

./datelist -A

Then just follow the prompts which are given to enter;
- file to read from
- number of numeric values to append (max 5)
- output filename


Prepending numeric values to the beginning of an existing
(date)wordlist with the -P switch
---------------------------------------------------------
As with the -A switch, you simply start datelist as follows;

./datelist -P

Then just follow the prompts which are given to enter;
- file to read from
- number of numeric values to append (max 5)
- output filename



BUGS/LIMITATIONS
================
Think slowly sorting things out.. however I am sure that things
will pop up after some time. 
Please comment if you find anything.


?COMMENTS?
==========
If you would liketo message me on datelist, to either scorn, ridicule
or laugh at me, feel free to do so; tape dot rulez at gmail dot com
:D


CHANGELOG
=========

v0.7
- Fixed a bug with the months of July being excluded.
- Fixed a bug with the leapyear calculations missing on whole century dates.
  Thanks to stepking2 for pointing the above bugs out to me !
- Included the -a and -p switch to allow to append or prepend word/characters
  to the created datelist from the command line.

v0.6
- Included more error checks for input dates and other entries.

v0.5
- Rewrote the method of creating dates so as not to have to be dependant on the 'date' command.
  No more limits on dates ! Yay ! 
  Also much faster.
- Fixed some temporary files not being deleted.

v0.4
- Made datelist able to be run directly from the command line instead of using 
  prompts also allowing input of custom filename for output.
- Improved the method of using spacing characters and the number of characters
  that can be used as spacing characters.
- Included possibilities for appending and prepending using custom files
  for input and output instead of being limited to file 'datelist.txt' as in v0.3.
- Tidied up code.

v0.3
- Tidied up some superfluous code
- Tidied up output when creating datelists
- Added switch -s to allow to insert one of 3 possible spacing characters ( - . / )
  in an existing datelist.txt file.

v0.2
- Added support for various output formats.
- Improved the reliability of different outputs.
- Included option to append/prepend upto 5 numbers.

v0.1 
First trials

('q' to quit)" | less
fi
exit
}
#
#
function help_info() {
clear
echo $BLUEBOLD"TAPE's_       _        _ _     _
     | |     | |      | (_)   | |  
   __| | __ _| |_  ___| |_ ___| |_ 
  / _  |/ _  | __|/ _ \ | / __| __|
 | (_| | (_| | |_ | __/ | \__ \ |_ 
  \____|\____|\__|\___|_|_|___/\__|
v0.7$STAND"
echo
echo "Usage: ./datelist -b [begin date] -e [end date] -f [date format] -o [output file]"
echo
echo "Required input;
-b  ---  Begin date$REDBOLD must be in format yyyy-mm-dd $STAND
-e  ---  End date$REDBOLD must be in format yyyy-mm-dd $STAND
-f  ---  Date format; ddmmyy / ddmmyyyy / mmddyy / mmddyyyy / yymmdd / yyyymmdd
-o  ---  Path/filename to write the datelist to

Optional input;
-a  ---- Append word/characters (some may need escaping with backslash $GREENBOLD\ $STAND)
-p  ---- Prepend word/characters (some may need escaping with backslash $GREENBOLD\ $STAND)
-s  ---- Desired spacing character ($GREENBOLD- / .$STAND etc. some may need escaping with backslash $GREENBOLD\ $STAND)

Alternative options;
-A  ---  Append numeric values to an existing wordlist (no other switches required)
-P  ---  Prepend numeric values to an existing wordlist (no other switches required)
-v  ---  Version & more detailed information on usage
-h  ---  This help information$GREENBOLD

Example:$STAND ./datelist -b 1900-01-01 -e 2050-12-31 -f ddmmyyyy -o date_wordlist.txt -s -
	$STAND ./datelist -b 1900-01-01 -e 2000-12-31 -f yymmdd -o date_wordlist.txt -p TEST"
echo $STAND""
exit 1
}
#
#
# Function to append upto 5 numeric values to an existing wordlist.
# When starting datelist for this function, only enter in command line ; ./datelist -A
# and then follow the prompts.
function append () {
echo -ne $STAND"Enter filename to append numeric characters to: "$GREENBOLD
read INFILE
(tput sgr0)
while [ ! -f $INFILE ] ; do
echo
echo $REDBOLD"File does not exist"$STAND
echo -en $STAND"Please enter full /path/to/file: "$GREENBOLD
read INFILE
(tput sgr0)
done
echo -ne $STAND"Enter how many numeric characters to append (max 5): "$GREENBOLD
read NUMB
(tput sgr0)
echo -ne $STAND"Enter output file name: "$GREENBOLD
read OUTFILE
(tput sgr0)
if [ -f "$OUTFILE" ] ; then
echo -ne $STAND"File $GREENBOLD$OUTFILE$STAND already exists, overwrite ? y/n $GREENBOLD"
read OVER
(tput sgr0)
	if [ "$OVER" = "y" ] || [ "$OVER" = "Y" ] ; then
	echo
	else
	echo $STAND"Process cancelled, quitting.."
	exit
	fi
fi
echo $STAND"Appending $GREENBOLD$NUMB$STAND digit(s) to $GREENBOLD$INFILE$STAND and writing to $GREENBOLD$OUTFILE$STAND ;"
 	if [ "$NUMB" == 1 ] ; then 
 	for i in $(cat $INFILE); do seq -f "$i%0$NUMB.0f" 0 9; done > "$OUTFILE"
 	elif [ "$NUMB" == 2 ] ; then 
 	for i in $(cat $INFILE); do seq -f "$i%0$NUMB.0f" 0 99; done > "$OUTFILE"
 	elif [ "$NUMB" == 3 ] ; then 
 	for i in $(cat $INFILE); do seq -f "$i%0$NUMB.0f" 0 999; done > "$OUTFILE"
 	elif [ "$NUMB" == 4 ] ; then 
 	for i in $(cat $INFILE); do seq -f "$i%0$NUMB.0f" 0 9999; done > "$OUTFILE"
 	elif [ "$NUMB" == 5 ] ; then 
 	for i in $(cat $INFILE); do seq -f "$i%0$NUMB.0f" 0 99999; done > "$OUTFILE"
 	fi
	head -3 $OUTFILE
	echo ".."
 	tail -3 $OUTFILE
exit
}
#
# Function to prepend upto 5 numeric values to an existing wordlist.
# When starting datelist for this function, only enter in command line ; ./datelist -P
# and then follow the prompts.
function prepend () {
echo -ne $STAND"Enter filename to prepend numeric characters to: "$GREENBOLD
read INFILE
(tput sgr0)
while [ ! -f $INFILE ] ; do
echo
echo $REDBOLD"File does not exist"$STAND
echo -en $STAND"Please enter full /path/to/file: "$GREENBOLD
read INFILE
(tput sgr0)
done
echo -ne $STAND"Enter how many numeric characters to prepend (max 5): "$GREENBOLD
read NUMB
(tput sgr0)
echo -ne $STAND"Enter output file name: "$GREENBOLD
read OUTFILE
(tput sgr0)
if [ -f "$OUTFILE" ] ; then
echo -ne $STAND"File $GREENBOLD$OUTFILE$STAND already exists, overwrite ? y/n $GREENBOLD"
read OVER
(tput sgr0)
	if [ "$OVER" = "y" ] || [ "$OVER" = "Y" ] ; then
	echo
	else
	echo $STAND"Process cancelled, quitting.."
	exit
	fi
fi
echo "Prepending $GREENBOLD$NUMB$STAND digit(s) to $GREENBOLD$INFILE$STAND and writing to $GREENBOLD$OUTFILE$STAND ;"
 	if [ "$NUMB" == 1 ] ; then 
 	for i in $(cat $INFILE); do seq -f "%0$NUMB.0f$i" 0 9; done > "$OUTFILE"
 	elif [ "$NUMB" == 2 ] ; then 
 	for i in $(cat $INFILE); do seq -f "%0$NUMB.0f$i" 0 99; done > "$OUTFILE"
 	elif [ "$NUMB" == 3 ] ; then 
 	for i in $(cat $INFILE); do seq -f "%0$NUMB.0f$i" 0 999; done > "$OUTFILE"
 	elif [ "$NUMB" == 4 ] ; then 
 	for i in $(cat $INFILE); do seq -f "%0$NUMB.0f$i" 0 9999; done > "$OUTFILE"
 	elif [ "$NUMB" == 5 ] ; then 
 	for i in $(cat $INFILE); do seq -f "%0$NUMB.0f$i" 0 99999; done > "$OUTFILE"
 	fi
	head -3 $OUTFILE
	echo ".."
 	tail -3 $OUTFILE
exit
}
#
#
#==================#
# Option arguments #
#------------------#
while getopts "Aa:b:e:f:ho:Pp:s:v" opt ; do
case ${opt} in
A) append;;
a) append_word=$OPTARG;;
b) begin_date=$OPTARG;;
e) end_date=$OPTARG;;
f) format=$OPTARG;;
o) date_outfile=$OPTARG;;
P) prepend;;
p) prepend_word=$OPTARG;;
s) space=$OPTARG;;
v) version;;
h) help_info;;
*) echo $REDBOLD"input error, see 'help' for usage"$STAND ; help
esac
done
shift $(($OPTIND - 1))
# 
#
trap control_c SIGINT
trap error_msg ERR
#
control_c () {
# Run if a Ctrl C is detected
echo $STAND" -- Control-C detected"
echo "$GREENBOLD>$STAND Checking for and removing any temp files .."
if [ -f dates_years ] ; then rm dates_years ; fi
if [ -f dates_months ] ; then rm dates_months ; fi
if [ -f datelist_temp ] ; then rm datelist_temp ; fi
if [ -f dates_sort.txt ] ; then rm dates_sort.txt ; fi
if [ -f date_list1_temp ] ; then rm date_list1_temp ; fi
exit
}
#
error_msg() {
echo $REDBOLD"Errors detected"
echo $STAND"Check that correct syntax is used"
echo "$GREENBOLD>$STAND Checking for and removing any temp files .."
if [ -f dates_years ] ; then rm dates_years ; fi
if [ -f dates_months ] ; then rm dates_months ; fi
if [ -f datelist_temp ] ; then rm datelist_temp ; fi
if [ -f dates_sort.txt ] ; then rm dates_sort.txt ; fi
if [ -f date_list1_temp ] ; then rm date_list1_temp ; fi
exit
}
#
#
######################################
######################################
##                                  ##
## MAIN DATELIST SCRIPT STARTS HERE ##
##                                  ##
######################################
######################################
{
clear
echo $BLUEBOLD"TAPE's_       _        _ _     _
     | |     | |      | (_)   | |  
   __| | __ _| |_  ___| |_ ___| |_ 
  / _  |/ _  | __|/ _ \ | / __| __|
 | (_| | (_| | |_ | __/ | \__ \ |_ 
  \____|\____|\__|\___|_|_|___/\__|
v0.7$STAND"
#
#
#Cut years, months and days for future reference and calculations
startyear=$(echo $begin_date | cut -d - -f 1)
startmonth=$(echo $begin_date | cut -d - -f 2)
startday=$(echo $begin_date | cut -d - -f 3)
endyear=$(echo $end_date | cut -d - -f 1)
endmonth=$(echo $end_date | cut -d - -f 2)
endday=$(echo $end_date | cut -d - -f 3)
#
#
#
#######################################
## Checking for incorrect data input ##
#######################################

# Return help menu if no / too little input given
if [[ -z "$begin_date" || -z "$end_date" || -z "$format" || -z "$date_outfile" ]] ; then
echo $REDBOLD"Need more input$STAND "
if [ -f dates_years ] ; then rm dates_years ; fi
if [ -f dates_months ] ; then rm dates_months ; fi
if [ -f datelist_temp ] ; then rm datelist_temp ; fi
if [ -f dates_sort.txt ] ; then rm dates_sort.txt ; fi
if [ -f date_list1_temp ] ; then rm date_list1_temp ; fi
echo "./datelist -h  for help"
echo
exit
fi
#
#
# Check for correct date output format
if  [[ "$format" == "ddmmyy" || "$format" == "ddmmyyyy" || "$format" == "mmddyy" || "$format" == "mmddyyyy" || "$format" == "yymmdd" || "$format" == "yyyymmdd" ]] ; then 
echo
else
echo $REDBOLD"Output format error: $format$STAND, must be one of the below formats;"
echo $GREENBOLD"ddmmyy / ddmmyyyy / mmddyy / mmddyyyy / yymmdd / yyyymmdd $STAND "
if [ -f dates_years ] ; then rm dates_years ; fi
if [ -f dates_months ] ; then rm dates_months ; fi
if [ -f datelist_temp ] ; then rm datelist_temp ; fi
if [ -f dates_sort.txt ] ; then rm dates_sort ; fi
if [ -f date_list1_temp ] ; then rm date_list1_temp ; fi
echo
echo $STAND"./datelist -h  for help"
echo
exit
fi
#
#
#Check for incorrect start date entry
syear_len=$(echo "$startyear" | wc -L)
if [[ "$syear_len" -ne 4 ]] ; then 
echo $REDBOLD"Begin year error: $startyear$STAND, year entries must have 4 digits"
echo "./datelist -h  for help"
echo
exit
fi
if [[ "$startmonth" -lt "01" || "$startmonth" -gt "12" ]] ; then
echo $REDBOLD"Begin month error: $startmonth$STAND, months can only be between 01 - 12"
echo $STAND"./datelist -h  for help"
echo
exit
fi
if [[ "$startday" -lt "01" || "$startday" -gt "31" ]] ; then
echo $REDBOLD"Begin day error: $startday$STAND, days can only be between 01 - 31"
echo $STAND"./datelist -h  for help"
echo
exit
fi
#
#
#Check for incorrect end date entry
eyear_len=$(echo "$endyear" | wc -L)
if [[ "$eyear_len" -ne 4 ]] ; then 
echo $REDBOLD"End year error: $endyear$STAND, year entries must have 4 digits"
echo "./datelist -h  for help"
echo
exit
fi
if [[ "$endmonth" -lt "01" || "$endmonth" -gt "12" ]] ; then
echo $REDBOLD"End month error: $endmonth$STAND, months can only be between 01 - 12"
echo $STAND"./datelist -h  for help"
echo
exit
fi
if [[ "$endday" -lt "01" || "$endday" -gt "31" ]] ; then
echo $REDBOLD"End day error: $endday$STAND, days can only be between 01 - 31"
echo $STAND"./datelist -h  for help"
echo
exit
fi
#
#
#Check that end date is not before start date
if [ "$startyear" -gt "$endyear" ] ; then 
echo $REDBOLD"Start/End date error:$STAND Start date cannot be greater than end date"
echo $STAND"./datelist -h  for help"
echo
exit
elif [[ "$startyear" -ge "$endyear" && "$startmonth" -gt "$endmonth" ]] ; then
echo $REDBOLD"Start/End date error:$STAND Start date cannot be greater than end date"
echo $STAND"./datelist -h  for help"
echo
exit
elif [[ "$startyear" -ge "$endyear" && "$startmonth" -ge "$endmonth" && "$startday" -gt "$endday" ]] ; then
echo $REDBOLD"Start/End date error:$STAND Start date cannot be greater than end date"
echo $STAND"./datelist -h  for help"
echo
exit
fi
#
#
#
#Check if desired output file already exists
if [ -f "$date_outfile" ] ; then 
echo -ne $STAND"File $GREENBOLD$date_outfile$STAND already exists, overwrite ? y/n $GREENBOLD"
read OVER
(tput sgr0)
	if [ "$OVER" = "y" ] || [ "$OVER" = "Y" ] ; then
	echo
	else
	echo $STAND"Process cancelled, quitting.."
	exit
	fi
fi
#
#
#Recap of datelist to be created.
if [ -n "$space" ] ; then
echo "Listing dates from $GREENBOLD$begin_date$STAND to $GREENBOLD$end_date$STAND in format $GREENBOLD$format$STAND with spacing character $GREENBOLD$space$STAND"
echo
elif [ -z "$space" ] ; then
echo "Listing dates from $GREENBOLD$begin_date$STAND to $GREENBOLD$end_date$STAND in format $GREENBOLD$format$STAND"
echo
fi
#
#
#Progress information
echo "$GREENBOLD>$STAND Listing range of years and months .."
#
#
#
#List the years
echo $startyear > dates_years
while [ "$startyear" != "$endyear" ] ; do 
startyear=$(expr $startyear + 1) 
echo $startyear >> dates_years
done
#
#Add a '-' spacer after the years to simplify later manipulations / calculations
sed 's/^.\{4\}/&-/' -i dates_years
#
#
#
#Add months to list of years
for i in $(cat dates_years) ; do seq -f $i%02.0f 01 12 ; done > dates_months
#
#Add a '-' spacer after the months to simplify later manipulations / calculations
sed 's/.$/&-/' -i dates_months
#
#
#
#Progress information
echo "$GREENBOLD>$STAND Checking for leapyears and listing correct days per month .."
#
#
#
#Add correct number of days per month to list of years & months
#A leap year is a year divisible by 4 but not by 100 unless it is also divisible by 400.
for i in $(cat dates_months)
	do
	mnth=$(echo $i | cut -d - -f 2)
	year=$(echo $i | cut -d - -f 1)
	if [[ "$mnth" == "02" ]] ; then
		if [[ `expr "$year" % 4` == 0 && `expr "$year" % 100` != 0 ]] ; then
		seq -f $i%02.0f 01 29
		elif [[ `expr "$year" % 4` == 0 && `expr "$year" % 100` != 0 && `expr "$year" % 400` == 0 ]] ; then
		seq -f $i%02.0f 01 29
		else
		seq -f $i%02.0f 01 28
		fi
	elif [[ "$mnth" == "04" || "$mnth" == "06" || "$mnth" == "09" || "$mnth" == "11" ]] ; then 
	seq -f $i%02.0f 01 30
	elif [[ "$mnth" == "01" || "$mnth" == "03" || "$mnth" == "05" || "$mnth" == "07" || "$mnth" == "08"  || "$mnth" == "10"|| "$mnth" == "12" ]] ; then 
	seq -f $i%02.0f 01 31 
	fi
	done > datelist_temp
#Remove dates before/after start/end date.
sed -n "/$begin_date/,/$end_date/p" datelist_temp > date_list1_temp
#
#
#
#Progress information
echo "$GREENBOLD>$STAND Creating desired format with spacing character (if any) .. "
#
#
# Ensure correct format and spacing character in output
# format ddmmyy
if [ "$format" == "ddmmyy" ] ; then
	if [ -n "$space" ] && [ "$space" == "/" ] ; then
	sed 's/^..//' -i date_list1_temp
	awk -F- '{print $3 $2 $1}' date_list1_temp > dates_sort.txt
	sed 's/\(.\{2\}\)/&\//;s/\(.\{5\}\)/&\//' dates_sort.txt > "$date_outfile"
	rm date_list1_temp && rm dates_sort.txt
	elif [ -n "$space" ] ; then
	sed 's/^..//' -i date_list1_temp
	awk -F- '{print $3 $2 $1}' date_list1_temp > dates_sort.txt
 	sed "s/\(.\{2\}\)/&"$space"/;s/\(.\{5\}\)/&$space/" dates_sort.txt > "$date_outfile"
	rm date_list1_temp && rm dates_sort.txt
 	elif [ -z "$space" ] ; then
	sed 's/^..//' -i date_list1_temp
	awk -F- '{print $3 $2 $1}' date_list1_temp > "$date_outfile"
	rm date_list1_temp
	fi
# format ddmmyyyy
elif [ "$format" == "ddmmyyyy" ] ; then
	if [ -n "$space" ] && [ "$space" == "/" ] ; then
	awk -F- '{print $3 $2 $1}' date_list1_temp > dates_sort.txt
	sed 's/\(.\{2\}\)/&\//;s/\(.\{5\}\)/&\//' dates_sort.txt > "$date_outfile"
	rm date_list1_temp && rm dates_sort.txt
	elif [ -n "$space" ] ; then
	awk -F- '{print $3 $2 $1}' date_list1_temp > dates_sort.txt
 	sed "s/\(.\{2\}\)/&"$space"/;s/\(.\{5\}\)/&$space/" dates_sort.txt > "$date_outfile"
	rm date_list1_temp && rm dates_sort.txt
 	elif [ -z "$space" ] ; then
	awk -F- '{print $3 $2 $1}' date_list1_temp > "$date_outfile"
	rm date_list1_temp
	fi
# format yymmdd
elif [ "$format" == "yymmdd" ] ; then
	if [ -n "$space" ] && [ "$space" == "/" ] ; then
	sed 's/^..//' -i date_list1_temp
	sed 's/-/\//g' date_list1_temp > "$date_outfile"
	rm date_list1_temp
	elif [ -n "$space" ] ; then
	sed 's/^..//' -i date_list1_temp
	sed "s/-/$space/g" date_list1_temp > "$date_outfile"
	rm date_list1_temp
 	elif [ -z "$space" ] ; then
	sed 's/^..//' -i date_list1_temp
	awk -F- '{print $1 $2 $3}' date_list1_temp > "$date_outfile"
	rm date_list1_temp
	fi
# format yyyymmdd
elif [ "$format" == "yyyymmdd" ] ; then
	if [ -n "$space" ] && [ "$space" == "/" ] ; then
	sed 's/-/\//g' date_list1_temp > "$date_outfile"
	rm date_list1_temp
	elif [ -n "$space" ] ; then
	sed "s/-/$space/g" date_list1_temp > "$date_outfile"
	rm date_list1_temp
	elif [ -z "$space" ] ; then
	awk -F- '{print $1 $2 $3}' date_list1_temp > "$date_outfile"
	rm date_list1_temp
	fi
#format mmddyyyy
elif [ "$format" == "mmddyyyy" ] ; then
if [ -n "$space" ] && [ "$space" == "/" ] ; then
	awk -F- '{print $2 $3 $1}' date_list1_temp > dates_sort.txt
	sed 's/\(.\{2\}\)/&\//;s/\(.\{5\}\)/&\//' dates_sort.txt > "$date_outfile"
	rm date_list1_temp && rm dates_sort.txt
	elif [ -n "$space" ] ; then
	awk -F- '{print $2 $3 $1}' date_list1_temp > dates_sort.txt
 	sed "s/\(.\{2\}\)/&"$space"/;s/\(.\{5\}\)/&$space/" dates_sort.txt > "$date_outfile"
	rm date_list1_temp && rm dates_sort.txt
	elif [ -z "$space" ] ; then
	awk -F- '{print $2 $3 $1}' date_list1_temp > "$date_outfile"
	rm date_list1_temp
	fi
#format mmddyy
elif [ "$format" == "mmddyy" ] ; then
if [ -n "$space" ] && [ "$space" == "/" ] ; then
	sed 's/^..//' -i date_list1_temp
	awk -F- '{print $2 $3 $1}' date_list1_temp > dates_sort.txt
	sed 's/\(.\{2\}\)/&\//;s/\(.\{5\}\)/&\//' dates_sort.txt > "$date_outfile"
	rm date_list1_temp && rm dates_sort.txt
	elif [ -n "$space" ] ; then
	sed 's/^..//' -i date_list1_temp
	awk -F- '{print $2 $3 $1}' date_list1_temp > dates_sort.txt
 	sed "s/\(.\{2\}\)/&"$space"/;s/\(.\{5\}\)/&$space/" dates_sort.txt > "$date_outfile"
	rm date_list1_temp && rm dates_sort.txt
	elif [ -z "$space" ] ; then
	sed 's/^..//' -i date_list1_temp
	awk -F- '{print $2 $3 $1}' date_list1_temp > "$date_outfile"
	rm date_list1_temp
	fi
fi
#
#
#
#Append word/character if so specified with -a switch
if [ -n "$append_word" ] ; then 
echo "$GREENBOLD>$STAND Appending word/characters as specified .."
sed "s/.$/&$append_word/" -i "$date_outfile"
fi
#
#
#
#Prepend word/characters if so specified with -p switch
if [ -n "$prepend_word" ] ; then 
echo "$GREENBOLD>$STAND Prepending word/characters as specified .."
sed "s/^./$prepend_word&/" -i "$date_outfile"
fi
#
#
#
# Remove created temp files
echo "$GREENBOLD>$STAND Tidying up .."
if [ -f dates_years ] ; then rm dates_years ; fi
if [ -f dates_months ] ; then rm dates_months ; fi
if [ -f datelist_temp ] ; then rm datelist_temp ; fi
if [ -f dates_sort.txt ] ; then rm dates_sort.txt ; fi
if [ -f date_list1_temp ] ; then rm date_list1_temp ; fi
#
#
#
#List examples of created file
echo $STAND""
echo "Datelist $GREENBOLD$date_outfile$STAND has been created ;" 
head -n 3 $date_outfile
echo ".."
tail -n 3 $date_outfile
echo $STAND ""
#
#
#
# THE END
exit
}

