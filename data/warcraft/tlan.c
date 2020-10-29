// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m梦[2;37;0m[2;37;0m", ({"meng"}));        
        set("gender", "女性");                
        set("long", "这是梦，一只强大的幻兽。[2;37;0m
它是唐澜的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "tlan");
        set("owner_name", "唐澜");
        set_temp("owner", "tlan");
        set_temp("owner_name", "唐澜");
        ::setup();
}
