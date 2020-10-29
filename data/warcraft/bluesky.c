// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m凤凰[2;37;0m[2;37;0m", ({"fenghuang"}));        
        set("gender", "女性");                
        set("long", "这就是传说中的凤凰。[2;37;0m
它是唐婉的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "bluesky");
        set("owner_name", "唐婉");
        set_temp("owner", "bluesky");
        set_temp("owner_name", "唐婉");
        ::setup();
}
