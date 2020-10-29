// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("马[2;37;0m[2;37;0m", ({"whistle_neverfree"}));        
        set("gender", "女性");                
        set("long", "马[2;37;0m
它是欧阳伟的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "cnbbca");
        set("owner_name", "欧阳伟");
        set_temp("owner", "cnbbca");
        set_temp("owner_name", "欧阳伟");
        ::setup();
}
