// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("菊花圆[2;37;0m[2;37;0m", ({"juhua"}));        
        set("gender", "男性");                
        set("long", "菊花圆[2;37;0m
它是囤囤转的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ttz");
        set("owner_name", "囤囤转");
        set_temp("owner", "ttz");
        set_temp("owner_name", "囤囤转");
        ::setup();
}
