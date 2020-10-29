// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("瑞兽玉麒麟[2;37;0m[2;37;0m", ({"owenqilin"}));        
        set("gender", "男性");                
        set("long", "瑞兽玉麒麟[2;37;0m
它是张大千的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "dearowen");
        set("owner_name", "张大千");
        set_temp("owner", "dearowen");
        set_temp("owner_name", "张大千");
        ::setup();
}
