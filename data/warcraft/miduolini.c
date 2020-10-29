// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("魔幻兽[2;37;0m[2;37;0m", ({"mohuanshou"}));        
        set("gender", "男性");                
        set("long", "魔幻兽[2;37;0m
它是米多久的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "miduolini");
        set("owner_name", "米多久");
        set_temp("owner", "miduolini");
        set_temp("owner_name", "米多久");
        ::setup();
}
