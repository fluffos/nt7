// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m剑齿虎[2;37;0m[2;37;0m", ({"tiger"}));        
        set("gender", "男性");                
        set("long", "远古复活的神兽[2;37;0m
它是铁儿的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "tier");
        set("owner_name", "铁儿");
        set_temp("owner", "tier");
        set_temp("owner_name", "铁儿");
        ::setup();
}
