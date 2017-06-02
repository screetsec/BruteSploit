#!/usr/bin/perl
use strict;
use warnings;

my %permution = (
	"a" => [ "a", "4", "@", "&", "A" ],
	"b" => "bB",
	"c" => "cC",
	"d" => "dD",
	"e" => "3Ee",
	"f" => "fF",
	"g" => "gG9",
	"h" => "hH",
	"i" => "iI!|1",
	"j" => "jJ",
	"k" => "kK",
	"l" => "lL!71|",
	"m" => "mM",
	"n" => "nN",
	"o" => "oO0",
	"p" => "pP",
	"q" => "qQ",
	"r" => "rR",
	"s" => "sS5\$",
	"t" => "tT71+",
	"u" => "uU",
	"v" => "vV",
	"w" => ["w", "W", "\\/\\/"],
	"x" => "xX",
	"y" => "yY",
	"z" => "zZ2",
);

while(my $word = <>) {
	chomp $word;
	my @string = split //, lc($word);
	&permute(0, @string);
}

sub permute {
	my $num = shift;
	my @str = @_;
	my $len = @str;

	if($num >= $len) {
		foreach my $char (@str) {
			print $char;
		}
		print "\n";
		return;
	}

	my $per = $permution{$str[$num]};

	if($per) {
		my @letters = ();
		if(ref($per) eq "ARRAY") {
			@letters = @$per;
		} else {
			@letters = split //, $per;
		}
		$per = "";

		foreach $per (@letters) {
			my $s = "";
			for(my $i = 0; $i < $len; $i++) {
				if($i eq 0) {
					if($i eq $num) {
						$s = $per;
					} else {
						$s = $str[0];
					}
				} else {
					if($i eq $num) {
						$s .= $per;
					} else {
						$s .= $str[$i];
					}
				}
			}
			my @st = split //, $s;
			&permute(($num + 1), @st);
		}
	} else {
		&permute(($num + 1), @str);
	}
}
