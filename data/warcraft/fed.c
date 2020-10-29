// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "女性");                
        set("long", "一只麒麟[2;37;0m
它是任志强的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "fed");
        set("owner_name", "任志强");
        set_temp("owner", "fed");
        set_temp("owner_name", "任志强");
        ::setup();
}
