// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m啪啪啪啪啪啪[2;37;0m[2;37;0m", ({"qwe"}));        
        set("gender", "男性");                
        set("long", "shit[2;37;0m
它是跑跑啊的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ppa");
        set("owner_name", "跑跑啊");
        set_temp("owner", "ppa");
        set_temp("owner_name", "跑跑啊");
        ::setup();
}
