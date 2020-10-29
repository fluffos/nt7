// cruise-ob.c

#include "/clone/misc/belt_ob.h"

string long() 
{
        string msg; 
        
        msg = query("long"); 
        msg += "这是荷包鸡蛋(mlb)的勋章挂带。
";
        
        //return sort_string(msg, 64, 0); 
        return msg;
}

void owner_is_killed() { destruct(this_object()); } 