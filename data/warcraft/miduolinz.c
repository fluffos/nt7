// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("多姿麒麟[2;37;0m[2;37;0m", ({"miduozride"}));        
        set("gender", "男性");                
        set("long", "多姿麒麟[2;37;0m
它是米多子的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "miduolinz");
        set("owner_name", "米多子");
        set_temp("owner", "miduolinz");
        set_temp("owner_name", "米多子");
        ::setup();
}
