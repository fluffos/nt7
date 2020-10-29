// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m绿狐[2;37;0m[2;37;0m", ({"greenfox"}));        
        set("gender", "女性");                
        set("long", "$HIG$绿狐[2;37;0m
它是灯水母的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "medusa");
        set("owner_name", "灯水母");
        set_temp("owner", "medusa");
        set_temp("owner_name", "灯水母");
        ::setup();
}
