// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m雅马哈[5m[1;37m迅鹰[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "男性");                
        set("long", "kick[2;37;0m
它是樱木花道的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "bally");
        set("owner_name", "樱木花道");
        set_temp("owner", "bally");
        set_temp("owner_name", "樱木花道");
        ::setup();
}
