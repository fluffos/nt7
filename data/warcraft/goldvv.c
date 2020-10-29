// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("喂喂喂[2;37;0m[2;37;0m", ({"goldvvv"}));        
        set("gender", "男性");                
        set("long", "喂喂喂[2;37;0m
它是金微的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "goldvv");
        set("owner_name", "金微");
        set_temp("owner", "goldvv");
        set_temp("owner_name", "金微");
        ::setup();
}
