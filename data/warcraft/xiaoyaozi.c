// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("比特[2;37;0m[2;37;0m", ({"bit"}));        
        set("gender", "女性");                
        set("long", "比特特[2;37;0m
它是慕容天的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xiaoyaozi");
        set("owner_name", "慕容天");
        set_temp("owner", "xiaoyaozi");
        set_temp("owner_name", "慕容天");
        ::setup();
}
