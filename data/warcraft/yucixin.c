// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("倾雪[2;37;0m[2;37;0m", ({"qingxue"}));        
        set("gender", "男性");                
        set("long", "倾雪[2;37;0m
它是玉辞心的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yucixin");
        set("owner_name", "玉辞心");
        set_temp("owner", "yucixin");
        set_temp("owner_name", "玉辞心");
        ::setup();
}
