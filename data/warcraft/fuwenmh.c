// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("四不像[2;37;0m[2;37;0m", ({"laoma"}));        
        set("gender", "男性");                
        set("long", "四不像[2;37;0m
它是唐小莹的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "fuwenmh");
        set("owner_name", "唐小莹");
        set_temp("owner", "fuwenmh");
        set_temp("owner_name", "唐小莹");
        ::setup();
}
