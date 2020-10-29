// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "男性");                
        set("long", "啊[2;37;0m
它是打想的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "jbc");
        set("owner_name", "打想");
        set_temp("owner", "jbc");
        set_temp("owner_name", "打想");
        ::setup();
}
