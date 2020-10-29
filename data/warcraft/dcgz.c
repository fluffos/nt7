// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[41;1m[1;37m沁宝贝[2;37;0m[2;37;0m", ({"julce"}));        
        set("gender", "女性");                
        set("long", "沁宝贝[2;37;0m
它是大肠干燥的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "dcgz");
        set("owner_name", "大肠干燥");
        set_temp("owner", "dcgz");
        set_temp("owner_name", "大肠干燥");
        ::setup();
}
