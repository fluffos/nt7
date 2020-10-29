// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("宝宝[2;37;0m[2;37;0m", ({"diysdfs"}));        
        set("gender", "男性");                
        set("long", "抱宝宝[2;37;0m
它是灵狐虫虫的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "diyzzywuwu");
        set("owner_name", "灵狐虫虫");
        set_temp("owner", "diyzzywuwu");
        set_temp("owner_name", "灵狐虫虫");
        ::setup();
}
