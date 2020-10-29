// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m梦[2;37;0m[2;37;0m", ({"meng"}));        
        set("gender", "女性");                
        set("long", "这是就是梦。[2;37;0m
它是唐雪的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "tanglan");
        set("owner_name", "唐雪");
        set_temp("owner", "tanglan");
        set_temp("owner_name", "唐雪");
        ::setup();
}
