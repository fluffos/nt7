// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("宝宝的坐骑[2;37;0m[2;37;0m", ({"lautmbb"}));        
        set("gender", "男性");                
        set("long", "宝宝的坐骑[2;37;0m
它是唐宝宝的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lautm");
        set("owner_name", "唐宝宝");
        set_temp("owner", "lautm");
        set_temp("owner_name", "唐宝宝");
        ::setup();
}
