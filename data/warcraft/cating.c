// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小红帽[2;37;0m[2;37;0m", ({"redmao"}));        
        set("gender", "男性");                
        set("long", "小红帽[2;37;0m
它是猫咪的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "cating");
        set("owner_name", "猫咪");
        set_temp("owner", "cating");
        set_temp("owner_name", "猫咪");
        ::setup();
}
