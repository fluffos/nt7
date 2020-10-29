// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("坐骑[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "男性");                
        set("long", "1111[2;37;0m
它是刀剑箫的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "crazya");
        set("owner_name", "刀剑箫");
        set_temp("owner", "crazya");
        set_temp("owner_name", "刀剑箫");
        ::setup();
}
