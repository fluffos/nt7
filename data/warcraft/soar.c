// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("美女[2;37;0m[2;37;0m", ({"kissy"}));        
        set("gender", "女性");                
        set("long", "白色[2;37;0m
它是龙翔的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "soar");
        set("owner_name", "龙翔");
        set_temp("owner", "soar");
        set_temp("owner_name", "龙翔");
        ::setup();
}
