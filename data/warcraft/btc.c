// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m玛莎啦蒂[2;37;0m[2;37;0m", ({"msa"}));        
        set("gender", "女性");                
        set("long", "finish[2;37;0m
它是周叁丹的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "btc");
        set("owner_name", "周叁丹");
        set_temp("owner", "btc");
        set_temp("owner_name", "周叁丹");
        ::setup();
}
