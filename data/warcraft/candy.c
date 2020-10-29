// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("宝贝[2;37;0m[2;37;0m", ({"baobei"}));        
        set("gender", "男性");                
        set("long", "宝贝[2;37;0m
它是反璞归真的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "candy");
        set("owner_name", "反璞归真");
        set_temp("owner", "candy");
        set_temp("owner_name", "反璞归真");
        ::setup();
}
