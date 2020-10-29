// cruise-ob.c

#include "/clone/misc/qiankun_ob.h"

string long() 
{
        string msg; 
        
        msg = query("long"); 
        msg += "这是角色扮演(rpg)的如意乾坤袋。
";
        msg += extra_long();
        
        //return sort_string(msg, 64, 0); 
        return msg;
}

void owner_is_killed() { destruct(this_object()); } 