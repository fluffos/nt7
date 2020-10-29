// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青鸾[2;37;0m[2;37;0m", ({"qingluan"}));        
        set("gender", "男性");                
        set("long", "青鸾杳，碧天云海音绝[2;37;0m
它是白玉京的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "byj");
        set("owner_name", "白玉京");
        set_temp("owner", "byj");
        set_temp("owner_name", "白玉京");
        ::setup();
}
