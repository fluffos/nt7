// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("瑞兽玉麒麟[2;37;0m[2;37;0m", ({"monksqilin"}));        
        set("gender", "男性");                
        set("long", "瑞兽玉麒麟[2;37;0m
它是张和尚的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "monkmike");
        set("owner_name", "张和尚");
        set_temp("owner", "monkmike");
        set_temp("owner_name", "张和尚");
        ::setup();
}
