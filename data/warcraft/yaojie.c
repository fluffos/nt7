// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青牛[2;37;0m[2;37;0m", ({"qingniu"}));        
        set("gender", "男性");                
        set("long", "青牛[2;37;0m
它是药杰的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "yaojie");
        set("owner_name", "药杰");
        set_temp("owner", "yaojie");
        set_temp("owner_name", "药杰");
        ::setup();
}
