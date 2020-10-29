// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火凤凰[2;37;0m[2;37;0m", ({"bird"}));        
        set("gender", "男性");                
        set("long", "远古来的一只会喷火的巨鸟。[2;37;0m
它是跑断腿的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "pdt");
        set("owner_name", "跑断腿");
        set_temp("owner", "pdt");
        set_temp("owner_name", "跑断腿");
        ::setup();
}
