// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"shinning"}));        
        set("gender", "男性");                
        set("long", "hello![2;37;0m
它是星月的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "moonstar");
        set("owner_name", "星月");
        set_temp("owner", "moonstar");
        set_temp("owner_name", "星月");
        ::setup();
}
