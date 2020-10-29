// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("太阳神鸟[2;37;0m[2;37;0m", ({"birdman"}));        
        set("gender", "男性");                
        set("long", "太阳神鸟[2;37;0m
它是血色太阳的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "scdyzxd");
        set("owner_name", "血色太阳");
        set_temp("owner", "scdyzxd");
        set_temp("owner_name", "血色太阳");
        ::setup();
}
