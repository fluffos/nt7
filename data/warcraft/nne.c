// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小眼[2;37;0m[2;37;0m", ({"myzuoqi"}));        
        set("gender", "女性");                
        set("long", "小眼[2;37;0m
它是很好噢噢的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "nne");
        set("owner_name", "很好噢噢");
        set_temp("owner", "nne");
        set_temp("owner_name", "很好噢噢");
        ::setup();
}
