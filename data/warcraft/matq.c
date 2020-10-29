// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m叁雪[2;37;0m[2;37;0m", ({"matqpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是雪叁的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "matq");
        set("owner_name", "雪叁");
        set_temp("owner", "matq");
        set_temp("owner_name", "雪叁");
        ::setup();
}
