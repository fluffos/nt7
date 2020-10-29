// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("睡神[2;37;0m[2;37;0m", ({"sleepbaga"}));        
        set("gender", "男性");                
        set("long", "睡神[2;37;0m
它是呢喃的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "iank");
        set("owner_name", "呢喃");
        set_temp("owner", "iank");
        set_temp("owner_name", "呢喃");
        ::setup();
}
