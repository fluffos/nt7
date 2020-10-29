// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("贾宝玉[2;37;0m[2;37;0m", ({"jbaoyu"}));        
        set("gender", "男性");                
        set("long", "贾宝玉[2;37;0m
它是熙凤的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "hxifeng");
        set("owner_name", "熙凤");
        set_temp("owner", "hxifeng");
        set_temp("owner_name", "熙凤");
        ::setup();
}
