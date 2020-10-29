// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小蛇[2;37;0m[2;37;0m", ({"xshe"}));        
        set("gender", "男性");                
        set("long", "小蛇[2;37;0m
它是小乞丐的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xqg");
        set("owner_name", "小乞丐");
        set_temp("owner", "xqg");
        set_temp("owner_name", "小乞丐");
        ::setup();
}
