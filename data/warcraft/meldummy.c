// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("欢乐的果[2;37;0m[2;37;0m", ({"choose"}));        
        set("gender", "男性");                
        set("long", "欢乐的果[2;37;0m
它是米甲秋的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "meldummy");
        set("owner_name", "米甲秋");
        set_temp("owner", "meldummy");
        set_temp("owner_name", "米甲秋");
        ::setup();
}
