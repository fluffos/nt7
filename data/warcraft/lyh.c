// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m太乙分光剑[2;37;0m[2;37;0m[2;37;0m", ({"xianjian"}));        
        set("gender", "男性");                
        set("long", "太乙分光剑[2;37;0m
它是木燕山的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lyh");
        set("owner_name", "木燕山");
        set_temp("owner", "lyh");
        set_temp("owner_name", "木燕山");
        ::setup();
}
