// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m树新蜂[2;37;0m[2;37;0m", ({"treenewbee"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是牛逼的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "newbee");
        set("owner_name", "牛逼");
        set_temp("owner", "newbee");
        set_temp("owner_name", "牛逼");
        ::setup();
}
