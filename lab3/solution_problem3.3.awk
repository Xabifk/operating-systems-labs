BEGIN { sum_first_2 = 0; sum_first_2_odd = 0; sum_first_2_odd_5_numbers = 0; sum_first_column = 0; sum_all = 0; }
{
	sum_first_2 += $1 + $2;
	sum_first_column += $1;

	for(i = 1; i <= NF; i++)
	{
		sum_all += $i;
	}

	if(NR % 2 == 1)
	{
		sum_first_2_odd += $1 + $2;
	}

	if(NR % 2 == 1 && NF == 5)
	{
		sum_first_2_odd_5_numbers+= $1 + $2;
	}
}
END { print sum_first_2; print sum_first_2_odd; print sum_first_2_odd_5_numbers; print sum_first_column; print sum_all; }

