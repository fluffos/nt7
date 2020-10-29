// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("山中精灵[2;37;0m[2;37;0m", ({"grace"}));        
        set("gender", "女性");                
        set("long", "山中精灵[2;37;0m
它是杜铭萱的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kelly");
        set("owner_name", "杜铭萱");
        set_temp("owner", "kelly");
        set_temp("owner_name", "杜铭萱");
        ::setup();
}
