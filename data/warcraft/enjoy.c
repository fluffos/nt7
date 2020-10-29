// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m死亡之吼[2;37;0m[2;37;0m", ({"laoma"}));        
        set("gender", "男性");                
        set("long", "死亡之吼[2;37;0m
它是虫二的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "enjoy");
        set("owner_name", "虫二");
        set_temp("owner", "enjoy");
        set_temp("owner_name", "虫二");
        ::setup();
}
