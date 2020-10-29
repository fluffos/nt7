// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟玉[2;37;0m[2;37;0m", ({"callme"}));        
        set("gender", "女性");                
        set("long", "没得[2;37;0m
它是龙龙酒的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "call");
        set("owner_name", "龙龙酒");
        set_temp("owner", "call");
        set_temp("owner_name", "龙龙酒");
        ::setup();
}
