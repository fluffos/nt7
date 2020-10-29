// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("圣麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "这是一只圣麒麟。[2;37;0m
它是一色的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yise");
        set("owner_name", "一色");
        set_temp("owner", "yise");
        set_temp("owner_name", "一色");
        ::setup();
}
