// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"dargon"}));        
        set("gender", "男性");                
        set("long", "一条青龙[2;37;0m
它是苏黄的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "suhuang");
        set("owner_name", "苏黄");
        set_temp("owner", "suhuang");
        set_temp("owner_name", "苏黄");
        ::setup();
}
