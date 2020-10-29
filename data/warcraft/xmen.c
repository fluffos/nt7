// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m踏雪[1;35m樱花驹[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "男性");                
        set("long", "这匹神驹通体如雪，背上点点樱花，貌似潘安、性如西门。[2;37;0m
它是西门庆的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xmen");
        set("owner_name", "西门庆");
        set_temp("owner", "xmen");
        set_temp("owner_name", "西门庆");
        ::setup();
}
