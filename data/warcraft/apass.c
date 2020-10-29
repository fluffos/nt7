// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("发生的额[2;37;0m[2;37;0m", ({"sdfw"}));        
        set("gender", "男性");                
        set("long", "发生的额[2;37;0m
它是水电费的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "apass");
        set("owner_name", "水电费");
        set_temp("owner", "apass");
        set_temp("owner_name", "水电费");
        ::setup();
}
