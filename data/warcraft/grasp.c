// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"whitetiger"}));        
        set("gender", "女性");                
        set("long", "小[2;37;0m
它是司空摘心的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "grasp");
        set("owner_name", "司空摘心");
        set_temp("owner", "grasp");
        set_temp("owner_name", "司空摘心");
        ::setup();
}
