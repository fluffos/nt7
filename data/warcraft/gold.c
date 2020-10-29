// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"benz"}));        
        set("gender", "男性");                
        set("long", "            [2;37;0m
它是黄金搭档的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "gold");
        set("owner_name", "黄金搭档");
        set_temp("owner", "gold");
        set_temp("owner_name", "黄金搭档");
        ::setup();
}
