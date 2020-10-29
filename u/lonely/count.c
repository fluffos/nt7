void count(mixed a, mixed b, mixed c)
{
        string *usercount = allocate(3); 
        mixed result;
        
        usercount[0] = a;
        usercount[1] = b;
        usercount[2] = c;
        usercount = map(usercount, (: CHINESE_D->chinese_to_number($1) :)); 
        result = implode(usercount, (:$1+$2:));  
        return result;
}

