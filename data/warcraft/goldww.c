// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("喂喂喂[2;37;0m[2;37;0m", ({"goldwww"}));        
        set("gender", "男性");                
        set("long", "喂喂喂[2;37;0m
它是金娃的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "goldww");
        set("owner_name", "金娃");
        set_temp("owner", "goldww");
        set_temp("owner_name", "金娃");
        ::setup();
}
