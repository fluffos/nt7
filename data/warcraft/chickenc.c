// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("印度阿三[2;37;0m[2;37;0m", ({"dfla"}));        
        set("gender", "男性");                
        set("long", "印度阿三[2;37;0m
它是啊三的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "chickenc");
        set("owner_name", "啊三");
        set_temp("owner", "chickenc");
        set_temp("owner_name", "啊三");
        ::setup();
}
