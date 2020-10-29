// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m青龙[2;37;0m[2;37;0m", ({"long"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是令狐意淫的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "shao");
        set("owner_name", "令狐意淫");
        set_temp("owner", "shao");
        set_temp("owner_name", "令狐意淫");
        ::setup();
}
