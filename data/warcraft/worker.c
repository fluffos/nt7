// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("阴阳[2;37;0m[2;37;0m", ({"yinyang"}));        
        set("gender", "男性");                
        set("long", "finish[2;37;0m
它是工人的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "worker");
        set("owner_name", "工人");
        set_temp("owner", "worker");
        set_temp("owner_name", "工人");
        ::setup();
}
