// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("坐骑[2;37;0m[2;37;0m", ({"zuoqie"}));        
        set("gender", "男性");                
        set("long", "坐骑[2;37;0m
它是药师五的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "yaoshie");
        set("owner_name", "药师五");
        set_temp("owner", "yaoshie");
        set_temp("owner_name", "药师五");
        ::setup();
}
