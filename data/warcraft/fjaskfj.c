// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "女性");                
        set("long", "麒麟[2;37;0m
它是刘喀喀的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "fjaskfj");
        set("owner_name", "刘喀喀");
        set_temp("owner", "fjaskfj");
        set_temp("owner_name", "刘喀喀");
        ::setup();
}
