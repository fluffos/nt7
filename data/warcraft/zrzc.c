// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m苍老师[1;32m[2;37;0m[2;37;0m", ({"aoi"}));        
        set("gender", "女性");                
        set("long", "大家的老师[2;37;0m
它是粽三的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "zrzc");
        set("owner_name", "粽三");
        set_temp("owner", "zrzc");
        set_temp("owner_name", "粽三");
        ::setup();
}
