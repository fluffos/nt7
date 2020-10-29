// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m不死鸟[2;37;0m[2;37;0m", ({"busi"}));        
        set("gender", "男性");                
        set("long", "$RED$浴火重生[2;37;0m
它是楚真的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "qzckr");
        set("owner_name", "楚真");
        set_temp("owner", "qzckr");
        set_temp("owner_name", "楚真");
        ::setup();
}
