// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m雪狼[2;37;0m[2;37;0m", ({"wolf"}));        
        set("gender", "男性");                
        set("long", "雪狼[2;37;0m
它是雪域苍狼的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "snowwolf");
        set("owner_name", "雪域苍狼");
        set_temp("owner", "snowwolf");
        set_temp("owner_name", "雪域苍狼");
        ::setup();
}
