#!/usr/local/bin/perl


while(<>) {
	
	if (!$flag) {

		$flag = 1 if (/^-------- /);
		next;
	}
	
	if (/^([^\|]+)\|([^\|]+)/) {
	
		push(@list,"$1:$2");
	}

	last if (/^$/);
}

system("fetch -f @list");
