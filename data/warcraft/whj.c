// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("脚趾头[2;37;0m[2;37;0m", ({"iiid"}));        
        set("gender", "男性");                
        set("long", "可[2;37;0m
它是唐四的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "whj");
        set("owner_name", "唐四");
        set_temp("owner", "whj");
        set_temp("owner_name", "唐四");
        ::setup();
}
