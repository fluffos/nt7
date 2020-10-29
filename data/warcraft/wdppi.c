// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("哦我的[2;37;0m[2;37;0m", ({"mygift"}));        
        set("gender", "女性");                
        set("long", "哦我的[2;37;0m
它是武当师九的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wdppi");
        set("owner_name", "武当师九");
        set_temp("owner", "wdppi");
        set_temp("owner_name", "武当师九");
        ::setup();
}
