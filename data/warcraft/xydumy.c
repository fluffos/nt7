// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("睡袋[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "一个睡袋[2;37;0m
它是逍遥快活的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xydumy");
        set("owner_name", "逍遥快活");
        set_temp("owner", "xydumy");
        set_temp("owner_name", "逍遥快活");
        ::setup();
}
