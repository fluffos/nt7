// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("从二飞翔[2;37;0m[2;37;0m", ({"forcebb"}));        
        set("gender", "女性");                
        set("long", "自由的飞翔[2;37;0m
它是内力从七的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "forceqi");
        set("owner_name", "内力从七");
        set_temp("owner", "forceqi");
        set_temp("owner_name", "内力从七");
        ::setup();
}
