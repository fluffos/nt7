// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("筋斗云[2;37;0m[2;37;0m", ({"jdy"}));        
        set("gender", "男性");                
        set("long", "筋斗云[2;37;0m
它是素页手札的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "skyamo");
        set("owner_name", "素页手札");
        set_temp("owner", "skyamo");
        set_temp("owner_name", "素页手札");
        ::setup();
}
