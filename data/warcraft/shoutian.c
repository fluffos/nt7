// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("永旭之巅[2;37;0m[2;37;0m", ({"yongxu"}));        
        set("gender", "男性");                
        set("long", "永旭之巅[2;37;0m
它是倦收天的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "shoutian");
        set("owner_name", "倦收天");
        set_temp("owner", "shoutian");
        set_temp("owner_name", "倦收天");
        ::setup();
}
