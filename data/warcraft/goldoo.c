// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("噢噢噢[2;37;0m[2;37;0m", ({"goldooo"}));        
        set("gender", "男性");                
        set("long", "噢噢噢[2;37;0m
它是金哦的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "goldoo");
        set("owner_name", "金哦");
        set_temp("owner", "goldoo");
        set_temp("owner_name", "金哦");
        ::setup();
}
