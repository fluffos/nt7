// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m人力三轮[2;37;0m[2;37;0m", ({"coo"}));        
        set("gender", "女性");                
        set("long", "$HIW$人力三轮[2;37;0m
它是做丹卖的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kooc");
        set("owner_name", "做丹卖");
        set_temp("owner", "kooc");
        set_temp("owner_name", "做丹卖");
        ::setup();
}
