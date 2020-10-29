// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m皮娃娃[5m[1;37m刘强东[2;37;0m[2;37;0m", ({"car"}));        
        set("gender", "男性");                
        set("long", "这是京东销量排名第一的刘强东版皮娃娃，众多少女闺房必备。[2;37;0m
它是章泽天的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "nai");
        set("owner_name", "章泽天");
        set_temp("owner", "nai");
        set_temp("owner_name", "章泽天");
        ::setup();
}
