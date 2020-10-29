// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("魔法扫把[2;37;0m[2;37;0m", ({"xxxxx"}));        
        set("gender", "男性");                
        set("long", "xxxxx[2;37;0m
它是七天的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "seven");
        set("owner_name", "七天");
        set_temp("owner", "seven");
        set_temp("owner_name", "七天");
        ::setup();
}
