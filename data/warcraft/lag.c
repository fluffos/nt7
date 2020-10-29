// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("玉佛珠[2;37;0m[2;37;0m", ({"out"}));        
        set("gender", "女性");                
        set("long", "此物品未鉴定[2;37;0m
它是赵灵儿的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lag");
        set("owner_name", "赵灵儿");
        set_temp("owner", "lag");
        set_temp("owner_name", "赵灵儿");
        ::setup();
}
