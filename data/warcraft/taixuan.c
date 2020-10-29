// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火麒麟[2;37;0m[2;37;0m", ({"huoqilin"}));        
        set("gender", "男性");                
        set("long", "  [2;37;0m
它是太玄的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "taixuan");
        set("owner_name", "太玄");
        set_temp("owner", "taixuan");
        set_temp("owner_name", "太玄");
        ::setup();
}
