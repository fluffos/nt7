// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m小辣椒[2;37;0m[2;37;0m", ({"xlj"}));        
        set("gender", "男性");                
        set("long", "很辣很辣的小辣椒。[2;37;0m
它是胡椒面的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "jojohu");
        set("owner_name", "胡椒面");
        set_temp("owner", "jojohu");
        set_temp("owner_name", "胡椒面");
        ::setup();
}
