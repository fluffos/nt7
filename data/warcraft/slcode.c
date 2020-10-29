// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[37m五色牛[2;37;0m[2;37;0m", ({"niu"}));        
        set("gender", "男性");                
        set("long", "五色牛[2;37;0m
它是灵台灵活的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "slcode");
        set("owner_name", "灵台灵活");
        set_temp("owner", "slcode");
        set_temp("owner_name", "灵台灵活");
        ::setup();
}
