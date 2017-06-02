#!/bin/bash
cd modules
# ↳
normal='\e[0m'
blue='\e[1;94m'
red='\e[1;31m'
yellow='\e[1;33m'
ul='\e[1;4m'
purp='\e[1;35m'
green='\e[1;32m'
white='\e[97m'
clear
echo -e "$white                      ______      $red  (                         "
echo -e "$white                   .-        -.   $red )\ )          )       (    "
echo -e "$white                  /            \  $red (()/(   (   ( /(    (  )\  "
echo -e "$white                 /              \ $red  /(_)) ))\  )\())  ))\((_) "
echo -e "$white                 |,  $red.-.  .-.$white ,| $red  (_))  /((_)((_)\  /((_)_   "
echo -e "$white                 | )$red(_ /  \_ )$white( | $white | _ \(_))  | |(_)(_)) | |  "
echo -e "$white                 |/     /\     \| $white |   // -_) | '_ \/ -_)| |  "
echo -e "$blue         _ $white      <__    ^^    __> $white |_|_|\\___| |_.__/\___||_|  "
echo -e " $red _     $blue) \_______${white}\__|${red}IIIIII${white}|__/${blue}___________________________"
echo -e " $red(_)\{}$blue<____________${white}__________${blue}_____________________________|>"
echo -e " $red      $blue )_/      $white   \ ${red}IIIIII${white} /$green                            ::"
echo -e "$white                   $white  --------   CODED BY MAGDY MOUSTAFA  $green {}"
	echo -e "                                                         $green ||"
	echo -e "$red	|                                                $green ()"
	echo -e "$red	|__$green Time    --> $( date | awk {' print $4 '} )"
	echo -e "$red	|__$green User    --> $( whoami )"
	echo -e "$red	|__$green Clone   --> https://github.com/rebellionil/rebel"
	echo -e "$red	|__$green Modules --> 6 modules"
if ! [[ $( whoami ) == "root" ]] ; then
	echo -e "$red	|__ Must Run As Root"
	exit
else
	sleep 0.5
	echo ""
fi

function modules {
	echo -e "$red	|__	   	  ${yellow}Mod${red}ules"
	echo -e "$red	|"
	echo -e "$red	|__$green sqli-search   ${red}==>       ${yellow}Search for sqli vurnable sites "
	echo -e "$red	|__$green map-lan       ${red}==>       ${yellow}Map all LAN devices "
	echo -e "$red	|__$green net-cut       ${red}==>       ${yellow}Cut off net on Lan devices "
	echo -e "$red	|__$green brute-r       ${red}==>       ${yellow}Bruteforce wide external subnetmasks "
	echo -e "$red	|__$green d-out         ${red}==>       ${yellow}Aireplay-ng automation for Deauth APs"
	echo -e "$red	|__$green lindum        ${red}==>       ${yellow}Dump sites links and extensions"
	echo ""
}
function help {
	echo -e "$red	|__		     ${yellow}H${red}elp"
	echo -e "$red	|"
	echo -e "$red	|__$green show modules     ${red}==>     ${yellow}List all available modules"
	echo -e "$red	|__$green use + modules    ${red}==>     ${yellow}Use this module name"
	echo -e "$red	|__$green show info        ${red}==>     ${yellow}Show module info"
	echo -e "$red	|__$green show options     ${red}==>     ${yellow}Show module options"
	echo -e "$red	|__$green set              ${red}==>     ${yellow}Set a value to an option"
	echo -e "$red	|__$green run              ${red}==>     ${yellow}Run module"
	echo -e "$red	|__$green clear            ${red}==>     ${yellow}Clear window"
	echo -e "$red	|__$green back             ${red}==>     ${yellow}Back to the main"
	echo -e "$red	|__$green exit             ${red}==>     ${yellow}Exit from rebel"
	echo -e "$red	|__$green help             ${red}==>     ${yellow}Show this message"
	echo ""
}
while true ; do
	echo -en "${red}[REBEL] > " ; read op1 op2 op3 op4 op5
	if [[ $op1 == "show" ]] && [[ $op2 == "modules" ]] ; then
		modules
	elif [[ $op1 == "help" ]] || [[ $op1 == "" ]] ; then
		help
	elif [[ $op1 == "use" ]] && [[ $op2 == "sqli-search" ]] ; then
		echo ""
		while true ; do
			echo -e "${red}[REBEL]"
			echo -en "${blue}   ↳${yellow}[ sqli-search ]${red} > " ; read opp1 opp2 opp3 opp4
			if [[ $opp1 == "run" ]] ; then
				bash samoon.sh
			elif [[ $opp1 == "show" ]] && [[ $opp2 == "info" ]] ; then
				echo -e "${blue}	|"
				echo -e "${blue}	|__ This module is searching for vurnable sqli sites using google dorks"
				echo ""
			elif [[ $opp1 == "show" ]] && [[ $opp2 == "options" ]] ; then
				echo -e "${blue}	|"
				echo -e "${blue}	|__ This module doesn't require any options , just run it :)"
				echo ""
                        elif [[ $opp1 == "clear" ]] ; then
                                clear
                        elif [[ $opp1 == "back" ]] || [[ $opp1 == "exit" ]] ; then
                                break
                        else
                                echo -e "${blue}           ↳${yellow} W${red}ong option "
                        fi
		done
	elif [[ $op1 == "use" ]] && [[ $op2 == "brute-r" ]] ; then
		wide="nul"
		range="nul"
		user="nul"
		pass="nul"
		echo ""
                while true ; do
                        echo -e "${red}[REBEL]"
                        echo -en "${blue}   ↳${yellow}[ brute-r ]${red} > " ; read opp1 opp2 opp3 opp4
			if [[ $opp1 == "show" ]] && [[ $opp2 == "info" ]] ; then
				echo -e "${blue}	|"
                                echo -e "${blue}	|__ This module can bruteforce wide ip range from routers by example,"
                                echo -e "${blue} 	|__ you can use it to automatically exploit some routers or cameras"
                                echo -e "${blue}	|__ just set requirements and run it :)"
				echo ""
			elif [[ $opp1 == "show" ]] && [[ $opp2 == "options" ]] ; then
				echo -e "${red}		options		value		ex"
				echo -e "${yellow}		-------		-----		--"
				echo ""
				echo -e "${red}		range	  $yellow	$range	$blue	197.40.50.1/16"
				echo -e "${red}		wide	  $yellow	$wide	$blue	[1-254] - --all "
				echo -e "${red}		user/USER $yellow	$user	$blue	user - ./wlists/user.txt"
				echo -e "${red}		pass/PASS $yellow	$pass	$blue	pass - ~/Desktop/pass.txt"
				echo ""
			elif [[ $opp1 == "set" ]] ; then
				if [[ $opp2 == "wide" ]] && [[ ! $opp3 == "" ]] ; then
					wide=$opp3
                                elif [[ $opp2 == "range" ]] && [[ ! $opp3 == "" ]] ; then
                                        range=$opp3
                                elif [[ $opp2 == "user" ]] && [[ ! $opp3 == "" ]] ; then
                                        user=$opp3
                                elif [[ $opp2 == "pass" ]] && [[ ! $opp3 == "" ]] ; then
                                        pass=$opp3
				fi
			elif [[ $opp1 == "run" ]] ; then
				if [[ $wide == "nul" ]] || [[ $range == "nul" ]] || [[ $pass == "nul" ]] || [[ $user == "nul" ]] ; then
                                	echo -e "${red}		[-] please set values to requirements before run module"
				elif [[ ! -f $pass ]] && [[ ! -f $user ]] ; then
					bash brute-R.sh $range $wide -l $user -p $pass
				elif [[ -f $user ]] && [[ ! -f $pass ]] ; then
                                        bash brute-R.sh $range $wide -L $user -p $pass
                                elif [[ -f $pass ]] && [[ ! -f $user ]] ; then
                                        bash brute-R.sh $range $wide -l $user -P $pass
                                elif [[ -f $user ]] && [[ -f $pass ]] ; then
                                        bash brute-R.sh $range $wide -L $user -P $pass
				fi
                        elif [[ $opp1 == "clear" ]] ; then
                                clear
                        elif [[ $opp1 == "back" ]] || [[ $opp1 == "exit" ]] ; then
                                break
                        else
                                echo -e "${blue}           ↳${yellow} W${red}ong option "
                        fi

		done
	elif [[ $op1 == "use" ]] && [[ $op2 == "map-lan" ]] ; then
		echo ""
		range="192.168.1.1/24"
		port_scan="true"
                while true ; do
                        echo -e "${red}[REBEL]"
                        echo -en "${blue}   ↳${yellow}[ map-LAN ]${red} > " ; read opp1 opp2 opp3 opp4
			if [[ $opp1 == "show" ]] && [[ $opp2 == "options" ]] ; then
                                echo -e "${red}         options         value           "
                                echo -e "${yellow}              -------         -----   "
                                echo ""
                                echo -e "${red}         range     $yellow       $range  "
			elif [[ $opp1 == "show" ]] && [[ $opp2 == "info" ]] ; then
				echo -e "${blue}	|__ nmap automation for map local area network [LAN]"
			elif [[ $opp1 == "set" ]] && [[ $opp2 == "range" ]] && [[ ! $opp3 == "" ]] ; then
					range=$opp3
			elif [[ $opp1 == "run" ]] ; then
					bash map-lan.sh $range
                        elif [[ $opp1 == "clear" ]] ; then
                                clear
                        elif [[ $opp1 == "back" ]] || [[ $opp1 == "exit" ]] ; then
                                break
                        else
                                echo -e "${blue}           ↳${yellow} W${red}ong option "
                        fi
		done
	elif [[ $op1 == "use" ]] && [[ $op2 == "d-out" ]] || [[ $op2 == "D-out" ]] ; then
		interface="wlan0"
                while true ; do
                        echo -e "${red}[REBEL]"
                        echo -en "${blue}   ↳${yellow}[ D-out ]${red} > " ; read opp1 opp2 opp3 opp4
			if [[ $opp1 == "show" ]] ; then
				if [[ $opp2 == "options" ]] ; then
	                                echo -e "${red}	options		value           "
        	                        echo -e "${yellow}	-------		-----   "
					echo ""
					echo -e "${blue}	interface	${yellow}$interface"
				        echo -e "$red   |__$green Interfaces "
        				for i in $( ifconfig | awk {' print $1 '} | grep ":" | cut -d ":" -f 1 ) ; do echo -e "$red             |__ $blue$i" ; done
				elif [[ $opp2 == "info" ]] ; then
					echo -e "${blue}	|__ this script will use airodump-ng, iwlist and aireplay"
					echo -e "${blue}	|__ to deuth access points [APs] and kick devices out of lan"
					echo -e "${blue}	|__ without being connected directly"
				fi
			elif [[ $opp1 == "set" ]] && [[ $opp2 == "interface" ]] ; then
				interface=$opp3
			elif [[ $opp1 == "run" ]] ; then
				bash D-out.sh $interface
                        elif [[ $opp1 == "clear" ]] ; then
                                clear
                        elif [[ $opp1 == "back" ]] || [[ $opp1 == "exit" ]] ; then
                                break
                        else
                                echo -e "${blue}           ↳${yellow} W${red}ong option "
                        fi
		done
	elif [[ $op1 == "use" ]] && [[ $op2 == "lindum" ]] ; then
		focus="png,pdf"
		rounds="5"
		target="google.com"
                while true ; do
                        echo -e "${red}[REBEL]"
                        echo -en "${blue}   ↳${yellow}[ Lindum ]${red} > " ; read opp1 opp2 opp3 opp4
			if [[ $opp1 == "show" ]] ; then
				if [[ $opp2 == "info" ]] ; then
					echo -e "${blue}	|__ This script will search for all links in main page site [ first round ]"
					echo -e "${blue}	|__ then rebeat on the same way with all found links at secound round and so on .."
				elif [[ $opp2 == "options" ]] ; then
                                        echo -e "${red}	options		value		ex"
                                        echo -e "${yellow}	-------		-----		--"
                                        echo ""
					echo -e "${blue}	Rounds$yellow		$rounds		${red}[1,2,3..]"
					echo -e "${blue}	Focus$yellow		$focus		${red}[all,pdf,png,jpg,admin,cpanel]"
					echo -e "${blue}	Target$yellow		$target		"
				fi
			elif [[ $opp1 == "run" ]] ; then
				if [[ $focus == "all" ]] ; then
					bash l_dumper.sh -u $target -r $rounds
				else
					focus=`echo $focus | sed 's/,/ -e /g'`
					bash l_dumper.sh -u $target -r $rounds | grep -e "Found" -e "Start" -e "Target" -e $focus
				fi

			elif [[ $opp1 == "set" ]] ; then

				if [[ $opp2 == "target" ]] ; then
					target=$opp3
				elif [[ $opp2 == "focus" ]] ; then
					focus=$opp3
				elif [[ $opp2 == "rounds" ]] ; then
					rounds=$opp3
				fi
                        elif [[ $opp1 == "clear" ]] ; then
                                clear
                        elif [[ $opp1 == "back" ]] || [[ $opp1 == "exit" ]] ; then
                                break
                        else
                                echo -e "${blue}           ↳${yellow} W${red}ong option "
                        fi
		done
	elif [[ $op1 == "use" ]] && [[ $op2 == "net-cut" ]] ; then
		interface="wlan0"
		target="all"
		getaway="192.168.1.1"
                while true ; do
                        echo -e "${red}[REBEL]"
                        echo -en "${blue}   ↳${yellow}[ Net-Cut ]${red} > " ; read opp1 opp2 opp3 opp4
			if [[ $opp1 == "show" ]] ; then
				if [[ $opp2 == "info" ]] ; then
					echo -e "${blue}	|__ This module can cut off connection  between victim and getaway using ARP spoof"
					echo ""
				elif [[ $opp2 == "options" ]] ; then
                                        echo -e "${red}	options		value		ex"
                                        echo -e "${yellow}	-------		-----		--"
                                        echo ""
					echo -e "${blue}	getaway$red		$getaway$yellow	'192.168.1.1'"
					echo -e "${blue}	interface$red	$interface$yellow		'wlan0' "
					echo -e "${blue}	target$red		$target$yellow		'all - 192.168.1.5 - 192.168.1.7,192.168.1.4,...'"
				fi
			elif [[ $opp1 == "set" ]] ; then
				if [[ $opp2 == "interface" ]] ; then
					interface=$opp3
				elif [[ $opp2 == "getaway" ]] ; then
					getaway=$opp3
				elif [[ $opp2 == "target" ]] ; then
					target=$opp3
				fi
			elif [[ $opp1 == "run" ]] ; then
					sudo bash netcut.sh $target $getaway $interface

                        elif [[ $opp1 == "clear" ]] ; then
                                clear
                        elif [[ $opp1 == "back" ]] || [[ $opp1 == "exit" ]] ; then
                                break
                        else
                                echo -e "${blue}           ↳${yellow} W${red}ong option "
			fi
		done
	elif [[ $op1 == "clear" ]] ; then
		clear
	elif [[ $op1 == "exit" ]] ; then
		exit 0
	else
		echo -e "${blue}   ↳${yellow} W${red}ong option "
	fi
done


