// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("宝贝[2;37;0m[2;37;0m", ({"qixuan"}));        
        set("gender", "女性");                
        set("long", "宝贝[2;37;0m
它是轩辕淇萱的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "qiqi");
        set("owner_name", "轩辕淇萱");
        set_temp("owner", "qiqi");
        set_temp("owner_name", "轩辕淇萱");
        ::setup();
}
