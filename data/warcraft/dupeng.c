// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("扫把[2;37;0m[2;37;0m", ({"shou"}));        
        set("gender", "男性");                
        set("long", "jj[2;37;0m
它是净蛋的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "dupeng");
        set("owner_name", "净蛋");
        set_temp("owner", "dupeng");
        set_temp("owner_name", "净蛋");
        ::setup();
}
