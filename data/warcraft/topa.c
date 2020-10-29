// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[31m飞天[1;37m神兽[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "男性");                
        set("long", "$BLINK$$RED$飞天$HIW$神兽[2;37;0m
它是发电机的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "topa");
        set("owner_name", "发电机");
        set_temp("owner", "topa");
        set_temp("owner_name", "发电机");
        ::setup();
}
