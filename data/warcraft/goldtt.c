// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("通天塔[2;37;0m[2;37;0m", ({"goldttt"}));        
        set("gender", "男性");                
        set("long", "通天塔[2;37;0m
它是金铁的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "goldtt");
        set("owner_name", "金铁");
        set_temp("owner", "goldtt");
        set_temp("owner_name", "金铁");
        ::setup();
}
