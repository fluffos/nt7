// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m万里长城[2;37;0m[2;37;0m", ({"sff"}));        
        set("gender", "男性");                
        set("long", "万里长城。。[2;37;0m
它是成城的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "chend");
        set("owner_name", "成城");
        set_temp("owner", "chend");
        set_temp("owner_name", "成城");
        ::setup();
}
