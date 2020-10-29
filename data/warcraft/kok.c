// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火凤凰[2;37;0m[2;37;0m", ({"phoenix"}));        
        set("gender", "男性");                
        set("long", "凤凰涅槃，浴火重生！[2;37;0m
它是王中王的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "kok");
        set("owner_name", "王中王");
        set_temp("owner", "kok");
        set_temp("owner_name", "王中王");
        ::setup();
}
