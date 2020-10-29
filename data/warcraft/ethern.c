// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("阿萨德[2;37;0m[2;37;0m", ({"hahaha"}));        
        set("gender", "女性");                
        set("long", "阿萨德[2;37;0m
它是以太闪电的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ethern");
        set("owner_name", "以太闪电");
        set_temp("owner", "ethern");
        set_temp("owner_name", "以太闪电");
        ::setup();
}
