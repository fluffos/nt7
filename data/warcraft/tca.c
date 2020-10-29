// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"choose"}));        
        set("gender", "女性");                
        set("long", "青龙[2;37;0m
它是菜农一的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "tca");
        set("owner_name", "菜农一");
        set_temp("owner", "tca");
        set_temp("owner_name", "菜农一");
        ::setup();
}
