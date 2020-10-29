// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("天宠[2;37;0m[2;37;0m", ({"dsf"}));        
        set("gender", "男性");                
        set("long", "一只仙兽，不知怎么流落到了人间。[2;37;0m
它是横刀的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "hdo");
        set("owner_name", "横刀");
        set_temp("owner", "hdo");
        set_temp("owner_name", "横刀");
        ::setup();
}
