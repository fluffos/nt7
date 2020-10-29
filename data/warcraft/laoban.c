// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"ddddd"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是老板的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "laoban");
        set("owner_name", "老板");
        set_temp("owner", "laoban");
        set_temp("owner_name", "老板");
        ::setup();
}
