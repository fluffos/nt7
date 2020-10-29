// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("球球[2;37;0m[2;37;0m", ({"xbai"}));        
        set("gender", "女性");                
        set("long", "球球[2;37;0m
它是尼姑的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "nig");
        set("owner_name", "尼姑");
        set_temp("owner", "nig");
        set_temp("owner_name", "尼姑");
        ::setup();
}
