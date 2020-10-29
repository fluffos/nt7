// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m墨鱼[2;37;0m[2;37;0m", ({"mql"}));        
        set("gender", "女性");                
        set("long", "小母龙哈[2;37;0m
它是小怪物的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ulianz");
        set("owner_name", "小怪物");
        set_temp("owner", "ulianz");
        set_temp("owner_name", "小怪物");
        ::setup();
}
