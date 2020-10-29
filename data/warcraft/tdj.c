// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m龙哥[2;37;0m[2;37;0m", ({"longge"}));        
        set("gender", "男性");                
        set("long", "龙[2;37;0m
它是六道轮回的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "tdj");
        set("owner_name", "六道轮回");
        set_temp("owner", "tdj");
        set_temp("owner_name", "六道轮回");
        ::setup();
}
