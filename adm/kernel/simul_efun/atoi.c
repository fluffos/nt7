// atoi.c

int atoi(mixed str)
{
        int v;

        if( intp(str) ) return str;
        if( !stringp(str) || ! sscanf(str, "%d", v) )
                return 0;

        return v;
}

string to_string(mixed arg)
{
        return stringp(arg) ? arg : save_variable(arg);
}

mixed abs(mixed n)
{
// #ifdef LONELY_IMPROVED
//      return efun::abs(n);
// #else

        if( !floatp(n) && !intp(n) )
                return 0;

        return (n < 0)? -n : n;
// #endif
}

mixed max(mixed a, mixed b)
{
        if( !floatp(a) && !intp(a) )
                return 0;

        if( !floatp(b) && !intp(b) )
                return 0;

        return a > b ? a : b;
}

mixed min(mixed a, mixed b)
{
        if( !floatp(a) && !intp(a) )
                return 0;

        if( !floatp(b) && !intp(b) )
                return 0;

        return a < b ? a : b;
}