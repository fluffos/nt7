// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小狗[2;37;0m[2;37;0m", ({"benz"}));        
        set("gender", "男性");                
        set("long", "        [2;37;0m
它是说说的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "soso");
        set("owner_name", "说说");
        set_temp("owner", "soso");
        set_temp("owner_name", "说说");
        ::setup();
}
