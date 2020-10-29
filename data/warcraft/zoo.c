// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火箭[2;37;0m[2;37;0m", ({"gooo"}));        
        set("gender", "男性");                
        set("long", "$HIR$火箭[2;37;0m
它是好汉饶命的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "zoo");
        set("owner_name", "好汉饶命");
        set_temp("owner", "zoo");
        set_temp("owner_name", "好汉饶命");
        ::setup();
}
