// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("多多[2;37;0m[2;37;0m", ({"btmxw"}));        
        set("gender", "男性");                
        set("long", "多了一个[2;37;0m
它是半条命的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "btm");
        set("owner_name", "半条命");
        set_temp("owner", "btm");
        set_temp("owner_name", "半条命");
        ::setup();
}
