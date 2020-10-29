// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"qing"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是菜农三的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "tcc");
        set("owner_name", "菜农三");
        set_temp("owner", "tcc");
        set_temp("owner_name", "菜农三");
        ::setup();
}
