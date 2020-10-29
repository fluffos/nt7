// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m张蝽龙[2;37;0m[2;37;0m", ({"loncly"}));        
        set("gender", "男性");                
        set("long", "瞄人缝大王的座骑，不要乱骑。[2;37;0m
它是瞄人缝的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lookbb");
        set("owner_name", "瞄人缝");
        set_temp("owner", "lookbb");
        set_temp("owner_name", "瞄人缝");
        ::setup();
}
