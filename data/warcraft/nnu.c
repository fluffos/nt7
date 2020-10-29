// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小眼[2;37;0m[2;37;0m", ({"myzuoqi"}));        
        set("gender", "女性");                
        set("long", "小眼[2;37;0m
它是黑钢飞刀的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "nnu");
        set("owner_name", "黑钢飞刀");
        set_temp("owner", "nnu");
        set_temp("owner_name", "黑钢飞刀");
        ::setup();
}
