// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[33m镇域神兽[2;37;0m[2;37;0m", ({"old"}));        
        set("gender", "男性");                
        set("long", "上天入地、擒妖斩魔[2;37;0m
它是老鬼的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "oldman");
        set("owner_name", "老鬼");
        set_temp("owner", "oldman");
        set_temp("owner_name", "老鬼");
        ::setup();
}
