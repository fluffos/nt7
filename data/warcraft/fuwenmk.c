// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("四不像[2;37;0m[2;37;0m", ({"laoma"}));        
        set("gender", "男性");                
        set("long", "四不像[2;37;0m
它是唐小韵的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "fuwenmk");
        set("owner_name", "唐小韵");
        set_temp("owner", "fuwenmk");
        set_temp("owner_name", "唐小韵");
        ::setup();
}
