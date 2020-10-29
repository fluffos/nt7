// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"ccss"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是学生的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ccs");
        set("owner_name", "学生");
        set_temp("owner", "ccs");
        set_temp("owner_name", "学生");
        ::setup();
}
