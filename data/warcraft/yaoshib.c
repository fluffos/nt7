// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("坐骑[2;37;0m[2;37;0m", ({"zuoqib"}));        
        set("gender", "男性");                
        set("long", "坐骑[2;37;0m
它是药师二的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "yaoshib");
        set("owner_name", "药师二");
        set_temp("owner", "yaoshib");
        set_temp("owner_name", "药师二");
        ::setup();
}
