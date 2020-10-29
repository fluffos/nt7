// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("衣魔[2;37;0m[2;37;0m", ({"moyiyi"}));        
        set("gender", "男性");                
        set("long", "衣魔[2;37;0m
它是魔衣的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "cloth");
        set("owner_name", "魔衣");
        set_temp("owner", "cloth");
        set_temp("owner_name", "魔衣");
        ::setup();
}
