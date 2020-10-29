// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m泡泡龙[2;37;0m[2;37;0m", ({"paopao"}));        
        set("gender", "女性");                
        set("long", "$HIM$泡泡龙[2;37;0m
它是随心的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lskx");
        set("owner_name", "随心");
        set_temp("owner", "lskx");
        set_temp("owner_name", "随心");
        ::setup();
}
