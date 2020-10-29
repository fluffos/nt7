// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"qingvi"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是菜农七的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "tcg");
        set("owner_name", "菜农七");
        set_temp("owner", "tcg");
        set_temp("owner_name", "菜农七");
        ::setup();
}
