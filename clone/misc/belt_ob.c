// cruise-ob.c

#include "/clone/misc/belt_ob.h"

string long() 
{
        string msg; 
        
        msg = query("long"); 
        msg += "LONG_DESCRIPTION";
        
        //return sort_string(msg, 64, 0); 
        return msg;
}

void owner_is_killed() { destruct(this_object()); } 