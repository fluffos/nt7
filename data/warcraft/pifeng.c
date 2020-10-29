// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m披魔[2;37;0m[2;37;0m", ({"pipipi"}));        
        set("gender", "男性");                
        set("long", "城[2;37;0m
它是魔披的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "pifeng");
        set("owner_name", "魔披");
        set_temp("owner", "pifeng");
        set_temp("owner_name", "魔披");
        ::setup();
}
