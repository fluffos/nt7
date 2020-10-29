// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m沃尔玛[2;37;0m[2;37;0m", ({"mall"}));        
        set("gender", "男性");                
        set("long", "沃尔玛[2;37;0m
它是水瓶座的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "aquarius");
        set("owner_name", "水瓶座");
        set_temp("owner", "aquarius");
        set_temp("owner_name", "水瓶座");
        ::setup();
}
