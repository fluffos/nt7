// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("坐骑[2;37;0m[2;37;0m", ({"zuoqic"}));        
        set("gender", "男性");                
        set("long", "坐骑[2;37;0m
它是药师三的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "yaoshic");
        set("owner_name", "药师三");
        set_temp("owner", "yaoshic");
        set_temp("owner_name", "药师三");
        ::setup();
}
