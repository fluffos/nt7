// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("坐骑[2;37;0m[2;37;0m", ({"zuoqid"}));        
        set("gender", "男性");                
        set("long", "坐骑[2;37;0m
它是药师四的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "yaoshid");
        set("owner_name", "药师四");
        set_temp("owner", "yaoshid");
        set_temp("owner_name", "药师四");
        ::setup();
}
