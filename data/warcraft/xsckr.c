// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m凤飞[2;37;0m[2;37;0m", ({"flying"}));        
        set("gender", "女性");                
        set("long", "$RED$凤飞[2;37;0m
它是楚雪的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xsckr");
        set("owner_name", "楚雪");
        set_temp("owner", "xsckr");
        set_temp("owner_name", "楚雪");
        ::setup();
}
