// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("打金麒麟[2;37;0m[2;37;0m", ({"dajinqilin"}));        
        set("gender", "女性");                
        set("long", "打金麒麟[2;37;0m
它是打金娃的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "dajin");
        set("owner_name", "打金娃");
        set_temp("owner", "dajin");
        set_temp("owner_name", "打金娃");
        ::setup();
}
