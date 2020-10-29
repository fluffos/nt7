// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m小小希[2;37;0m[2;37;0m", ({"xxx"}));        
        set("gender", "女性");                
        set("long", "小小希[2;37;0m
它是唐倩的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "tangqian");
        set("owner_name", "唐倩");
        set_temp("owner", "tangqian");
        set_temp("owner_name", "唐倩");
        ::setup();
}
