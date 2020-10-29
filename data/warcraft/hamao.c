// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("悠活[2;37;0m[2;37;0m", ({"yoho"}));        
        set("gender", "男性");                
        set("long", "无[2;37;0m
它是雪心的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "hamao");
        set("owner_name", "雪心");
        set_temp("owner", "hamao");
        set_temp("owner_name", "雪心");
        ::setup();
}
