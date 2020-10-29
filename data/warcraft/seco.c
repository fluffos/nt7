// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("扑克牌[2;37;0m[2;37;0m", ({"seso"}));        
        set("gender", "女性");                
        set("long", "老k[2;37;0m
它是西索的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "seco");
        set("owner_name", "西索");
        set_temp("owner", "seco");
        set_temp("owner_name", "西索");
        ::setup();
}
