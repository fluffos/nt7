// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老鹰[2;37;0m[2;37;0m", ({"baoma"}));        
        set("gender", "男性");                
        set("long", "老鹰[2;37;0m
它是药品专家的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "wdguiji");
        set("owner_name", "药品专家");
        set_temp("owner", "wdguiji");
        set_temp("owner_name", "药品专家");
        ::setup();
}
