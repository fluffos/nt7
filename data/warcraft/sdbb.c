// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("潜龙[2;37;0m[2;37;0m", ({"sdbaa"}));        
        set("gender", "男性");                
        set("long", "无所不及[2;37;0m
它是天空二号的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "sdbb");
        set("owner_name", "天空二号");
        set_temp("owner", "sdbb");
        set_temp("owner_name", "天空二号");
        ::setup();
}
