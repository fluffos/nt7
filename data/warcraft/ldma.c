// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("猪雀[2;37;0m[2;37;0m", ({"zqqqq"}));        
        set("gender", "女性");                
        set("long", "猪[2;37;0m
它是炼丹的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ldma");
        set("owner_name", "炼丹");
        set_temp("owner", "ldma");
        set_temp("owner_name", "炼丹");
        ::setup();
}
