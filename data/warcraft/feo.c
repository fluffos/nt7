// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("玄武[2;37;0m[2;37;0m", ({"ddddd"}));        
        set("gender", "男性");                
        set("long", "玄武[2;37;0m
它是怒海的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "feo");
        set("owner_name", "怒海");
        set_temp("owner", "feo");
        set_temp("owner_name", "怒海");
        ::setup();
}
