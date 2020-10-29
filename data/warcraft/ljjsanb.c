// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("酷跑[2;37;0m[2;37;0m", ({"pdk"}));        
        set("gender", "男性");                
        set("long", "酷跑[2;37;0m
它是散地的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ljjsanb");
        set("owner_name", "散地");
        set_temp("owner", "ljjsanb");
        set_temp("owner_name", "散地");
        ::setup();
}
