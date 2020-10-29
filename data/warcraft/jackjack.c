// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("祥云[2;37;0m[2;37;0m", ({"ire"}));        
        set("gender", "男性");                
        set("long", "“麟者，仁兽也，圣王之嘉瑞也[2;37;0m
它是真理的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "jackjack");
        set("owner_name", "真理");
        set_temp("owner", "jackjack");
        set_temp("owner_name", "真理");
        ::setup();
}
