// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("星云[2;37;0m[2;37;0m", ({"xingea"}));        
        set("gender", "男性");                
        set("long", "星云[2;37;0m
它是星云三的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xinge");
        set("owner_name", "星云三");
        set_temp("owner", "xinge");
        set_temp("owner_name", "星云三");
        ::setup();
}
