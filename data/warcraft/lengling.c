// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("棒棒[2;37;0m[2;37;0m", ({"bangbang"}));        
        set("gender", "男性");                
        set("long", "棒棒[2;37;0m
它是冷凌的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "lengling");
        set("owner_name", "冷凌");
        set_temp("owner", "lengling");
        set_temp("owner_name", "冷凌");
        ::setup();
}
