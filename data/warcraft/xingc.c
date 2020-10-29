// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("星云[2;37;0m[2;37;0m", ({"xingca"}));        
        set("gender", "男性");                
        set("long", "星云[2;37;0m
它是星飞的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xingc");
        set("owner_name", "星飞");
        set_temp("owner", "xingc");
        set_temp("owner_name", "星飞");
        ::setup();
}
