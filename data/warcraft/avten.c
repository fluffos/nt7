// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"qinlong"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是泷泽老师的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "avten");
        set("owner_name", "泷泽老师");
        set_temp("owner", "avten");
        set_temp("owner_name", "泷泽老师");
        ::setup();
}
