// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小眼[2;37;0m[2;37;0m", ({"myzuoqi"}));        
        set("gender", "女性");                
        set("long", "小眼[2;37;0m
它是合格产品的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "nnr");
        set("owner_name", "合格产品");
        set_temp("owner", "nnr");
        set_temp("owner_name", "合格产品");
        ::setup();
}
