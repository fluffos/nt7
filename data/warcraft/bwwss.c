// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("天乐麒麟[2;37;0m[2;37;0m", ({"ttqilin"}));        
        set("gender", "男性");                
        set("long", "这是bwwss的座机[2;37;0m
它是艳南天的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "bwwss");
        set("owner_name", "艳南天");
        set_temp("owner", "bwwss");
        set_temp("owner_name", "艳南天");
        ::setup();
}
