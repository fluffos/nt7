// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("火麒麟[2;37;0m[2;37;0m", ({"hqilin"}));        
        set("gender", "男性");                
        set("long", "火麒麟[2;37;0m
它是烈火的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lsao");
        set("owner_name", "烈火");
        set_temp("owner", "lsao");
        set_temp("owner_name", "烈火");
        ::setup();
}
