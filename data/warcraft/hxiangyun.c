// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("贾宝玉[2;37;0m[2;37;0m", ({"jbaoyu"}));        
        set("gender", "男性");                
        set("long", "贾宝玉[2;37;0m
它是湘云的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "hxiangyun");
        set("owner_name", "湘云");
        set_temp("owner", "hxiangyun");
        set_temp("owner_name", "湘云");
        ::setup();
}
