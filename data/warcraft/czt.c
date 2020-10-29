// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("菲尼克斯[2;37;0m[2;37;0m", ({"asd"}));        
        set("gender", "男性");                
        set("long", "菲尼克斯[2;37;0m
它是唐缺的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "czt");
        set("owner_name", "唐缺");
        set_temp("owner", "czt");
        set_temp("owner_name", "唐缺");
        ::setup();
}
