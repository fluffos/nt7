// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是炼甲的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "liandana");
        set("owner_name", "炼甲");
        set_temp("owner", "liandana");
        set_temp("owner_name", "炼甲");
        ::setup();
}
