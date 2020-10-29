// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("丁丁[2;37;0m[2;37;0m", ({"bruce"}));        
        set("gender", "男性");                
        set("long", "123[2;37;0m
它是史鸿雁的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "shy");
        set("owner_name", "史鸿雁");
        set_temp("owner", "shy");
        set_temp("owner_name", "史鸿雁");
        ::setup();
}
