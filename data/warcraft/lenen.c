// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m烈火凤凰[2;37;0m[2;37;0m[2;37;0m", ({"lao"}));        
        set("gender", "女性");                
        set("long", "一只烈火中永生的凤凰。[2;37;0m
它是唐大少的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lenen");
        set("owner_name", "唐大少");
        set_temp("owner", "lenen");
        set_temp("owner_name", "唐大少");
        ::setup();
}
