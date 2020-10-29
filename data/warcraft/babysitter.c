// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("保姆车[2;37;0m[2;37;0m", ({"baby"}));        
        set("gender", "男性");                
        set("long", "一台保姆车[2;37;0m
它是小保姆的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "babysitter");
        set("owner_name", "小保姆");
        set_temp("owner", "babysitter");
        set_temp("owner_name", "小保姆");
        ::setup();
}
