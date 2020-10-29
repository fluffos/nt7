// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m霹雳[1;31m赤焰驹[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "男性");                
        set("long", "这匹神驹通体赤焰般流动，声若霹雳、奔如闪电，故名赤焰兽。[2;37;0m
它是庞青云的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "pang");
        set("owner_name", "庞青云");
        set_temp("owner", "pang");
        set_temp("owner_name", "庞青云");
        ::setup();
}
