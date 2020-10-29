// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m武林列传[2;37;0m[2;37;0m", ({"wiiz"}));        
        set("gender", "女性");                
        set("long", "武林列传[2;37;0m
它是猪三的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wllz");
        set("owner_name", "猪三");
        set_temp("owner", "wllz");
        set_temp("owner_name", "猪三");
        ::setup();
}
