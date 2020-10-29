// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("坐骑[2;37;0m[2;37;0m", ({"zuoqia"}));        
        set("gender", "男性");                
        set("long", "坐骑[2;37;0m
它是药师一的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "yaoshia");
        set("owner_name", "药师一");
        set_temp("owner", "yaoshia");
        set_temp("owner_name", "药师一");
        ::setup();
}
