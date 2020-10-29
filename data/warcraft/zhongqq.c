// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("蛛蛛[2;37;0m[2;37;0m", ({"zhongqqq"}));        
        set("gender", "女性");                
        set("long", "蛛蛛[2;37;0m
它是钟魅的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "zhongqq");
        set("owner_name", "钟魅");
        set_temp("owner", "zhongqq");
        set_temp("owner_name", "钟魅");
        ::setup();
}
