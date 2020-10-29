// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("飞龙在天[2;37;0m[2;37;0m", ({"feilongzt"}));        
        set("gender", "男性");                
        set("long", "飞龙在天[2;37;0m
它是乾大虎的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "syqi");
        set("owner_name", "乾大虎");
        set_temp("owner", "syqi");
        set_temp("owner_name", "乾大虎");
        ::setup();
}
