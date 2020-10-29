// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小水[2;37;0m[2;37;0m", ({"aaalll"}));        
        set("gender", "男性");                
        set("long", "小水[2;37;0m
它是水月的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "zsyf");
        set("owner_name", "水月");
        set_temp("owner", "zsyf");
        set_temp("owner_name", "水月");
        ::setup();
}
