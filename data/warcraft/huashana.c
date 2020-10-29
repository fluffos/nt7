// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m的哥[2;37;0m[2;37;0m", ({"nannan"}));        
        set("gender", "男性");                
        set("long", "的哥[2;37;0m
它是华大哥的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "huashana");
        set("owner_name", "华大哥");
        set_temp("owner", "huashana");
        set_temp("owner_name", "华大哥");
        ::setup();
}
