// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"tou"}));        
        set("gender", "男性");                
        set("long", "一条青龙[2;37;0m
它是鹃鹏的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "hervour");
        set("owner_name", "鹃鹏");
        set_temp("owner", "hervour");
        set_temp("owner_name", "鹃鹏");
        ::setup();
}
