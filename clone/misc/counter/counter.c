// counter.c
//wsw于2004年2月20日
//玩家柜台
//玩家有此柜台后，可把物品摆在柜台上出售，重启后保留。
//如果是随机属性物品，物品->set("changed",1)

#include "counter.h"   

void create()
{        
        seteuid(0);
        set_name(HIC"柜台"NOR,({"counter" }) );   
        set_weight(50000);   
        /*if( clonep() )   
                set_default_object(__FILE__); 
        else*/ {   
        set("value", 2000000);   
   
                set("unit","个");   
                set("capacity",10);  //容量 
                set("no_put",1);   
                set("no_sell",1);   
                set("no_get",1);   
                set("no_give",1);   
                set("no_drop",1);   
                set("long",HIB"玩家之城的柜台。\n"NOR);   
        }   
        setup();     
}   