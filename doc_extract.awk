
getline
{
	while(getline == 1)
	{
		if(substr($0,0,10) == "/*********" ) print_comment()
	}
}


function print_comment()
{
	getline
	
	
	while( substr($0, 1, 1 ) != "*" )
	{
		print("line")
		print(substr($0, 1, length($0) - 2 ) )
		getline
	}
	print("done")	
}