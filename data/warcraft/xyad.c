// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("飞龙在天[2;37;0m[2;37;0m", ({"xyadl"}));        
        set("gender", "男性");                
        set("long", "停权[2;37;0m
它是圣人的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xyad");
        set("owner_name", "圣人");
        set_temp("owner", "xyad");
        set_temp("owner_name", "圣人");
        ::setup();
}
