// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("宝宝[2;37;0m[2;37;0m", ({"glflya"}));        
        set("gender", "男性");                
        set("long", "宝宝[2;37;0m
它是漂流子的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "cindy");
        set("owner_name", "漂流子");
        set_temp("owner", "cindy");
        set_temp("owner_name", "漂流子");
        ::setup();
}
