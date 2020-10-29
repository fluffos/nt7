// This program is a part of NT MudLIB

// valid_seteuid: determines whether an object ob can become euid str
int valid_seteuid(object ob, string str)
{
        if( find_object(SECURITY_D) )
                return (int)SECURITY_D->valid_seteuid( ob, str );
        return 1;
}
