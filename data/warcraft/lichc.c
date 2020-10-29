// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("阿斯顿飞剑[2;37;0m[2;37;0m", ({"sdfa"}));        
        set("gender", "男性");                
        set("long", "阿斯顿飞客垃圾死定了[2;37;0m
它是永生二的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "lichc");
        set("owner_name", "永生二");
        set_temp("owner", "lichc");
        set_temp("owner_name", "永生二");
        ::setup();
}
