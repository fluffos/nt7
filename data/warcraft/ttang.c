// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m青鸾[2;37;0m[2;37;0m", ({"que"}));        
        set("gender", "女性");                
        set("long", "一只凤凰的后代[2;37;0m
它是唐米唐的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ttang");
        set("owner_name", "唐米唐");
        set_temp("owner", "ttang");
        set_temp("owner_name", "唐米唐");
        ::setup();
}
