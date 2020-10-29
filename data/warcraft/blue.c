// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m貔貅[2;37;0m[2;37;0m", ({"pixiu"}));        
        set("gender", "男性");                
        set("long", "传说中的招财瑞兽，以财为食，纳食四方之财。[2;37;0m
它是唐蓝的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "blue");
        set("owner_name", "唐蓝");
        set_temp("owner", "blue");
        set_temp("owner_name", "唐蓝");
        ::setup();
}
