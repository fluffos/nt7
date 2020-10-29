// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("泥塘[2;37;0m[2;37;0m", ({"mohuanshou"}));        
        set("gender", "男性");                
        set("long", "泥塘[2;37;0m
它是米十一的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "miduolink");
        set("owner_name", "米十一");
        set_temp("owner", "miduolink");
        set_temp("owner_name", "米十一");
        ::setup();
}
