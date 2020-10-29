// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("客流量[2;37;0m[2;37;0m", ({"iiiu"}));        
        set("gender", "男性");                
        set("long", "客流量[2;37;0m
它是小牛的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lowekk");
        set("owner_name", "小牛");
        set_temp("owner", "lowekk");
        set_temp("owner_name", "小牛");
        ::setup();
}
