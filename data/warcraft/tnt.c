// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m戚长发[2;37;0m[2;37;0m", ({"tut"}));        
        set("gender", "男性");                
        set("long", "戚老板最近是爆发横财，所谓是三年不开张，开张管三年。[2;37;0m
它是重庆的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "tnt");
        set("owner_name", "重庆");
        set_temp("owner", "tnt");
        set_temp("owner_name", "重庆");
        ::setup();
}
