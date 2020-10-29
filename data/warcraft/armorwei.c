// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("套子[2;37;0m[2;37;0m", ({"beek"}));        
        set("gender", "男性");                
        set("long", "无[2;37;0m
它是百河愁的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "armorwei");
        set("owner_name", "百河愁");
        set_temp("owner", "armorwei");
        set_temp("owner_name", "百河愁");
        ::setup();
}
