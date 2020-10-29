// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m龙[1;37m暝[2;37;0m[2;37;0m", ({"att"}));        
        set("gender", "男性");                
        set("long", "幽驹戾天[2;37;0m
它是龙幽的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "frong");
        set("owner_name", "龙幽");
        set_temp("owner", "frong");
        set_temp("owner_name", "龙幽");
        ::setup();
}
