// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("淡定瑞兽麒麟[2;37;0m[2;37;0m", ({"owensqilin"}));        
        set("gender", "男性");                
        set("long", "淡定瑞兽玉麒麟[2;37;0m
它是张淡定的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "owen");
        set("owner_name", "张淡定");
        set_temp("owner", "owen");
        set_temp("owner_name", "张淡定");
        ::setup();
}
