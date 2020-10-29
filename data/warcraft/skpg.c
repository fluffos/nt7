// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"baihu"}));        
        set("gender", "男性");                
        set("long", "白虎[2;37;0m
它是郝连水的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "skpg");
        set("owner_name", "郝连水");
        set_temp("owner", "skpg");
        set_temp("owner_name", "郝连水");
        ::setup();
}
