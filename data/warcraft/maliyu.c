// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("布莱恩[2;37;0m[2;37;0m", ({"bryan"}));        
        set("gender", "男性");                
        set("long", "可爱聪明的布莱恩！[2;37;0m
它是张楚灵的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "maliyu");
        set("owner_name", "张楚灵");
        set_temp("owner", "maliyu");
        set_temp("owner_name", "张楚灵");
        ::setup();
}
