// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("龟龟[2;37;0m[2;37;0m", ({"budai"}));        
        set("gender", "男性");                
        set("long", "sdf[2;37;0m
它是努吧的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "dupengb");
        set("owner_name", "努吧");
        set_temp("owner", "dupengb");
        set_temp("owner_name", "努吧");
        ::setup();
}
