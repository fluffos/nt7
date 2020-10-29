// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m神圣麒麟[2;37;0m[2;37;0m", ({"gql"}));        
        set("gender", "女性");                
        set("long", "麒麟[2;37;0m
它是赵飞虎的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "gwire");
        set("owner_name", "赵飞虎");
        set_temp("owner", "gwire");
        set_temp("owner_name", "赵飞虎");
        ::setup();
}
