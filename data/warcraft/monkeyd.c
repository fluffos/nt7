// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("四不像[2;37;0m[2;37;0m", ({"laoma"}));        
        set("gender", "男性");                
        set("long", "四不像[2;37;0m
它是唐朋的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "monkeyd");
        set("owner_name", "唐朋");
        set_temp("owner", "monkeyd");
        set_temp("owner_name", "唐朋");
        ::setup();
}
