// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m菜青虫[2;37;0m[2;37;0m", ({"dragon"}));        
        set("gender", "男性");                
        set("long", "`(*∩_∩*)′[2;37;0m
它是影清斜的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "canwdc");
        set("owner_name", "影清斜");
        set_temp("owner", "canwdc");
        set_temp("owner_name", "影清斜");
        ::setup();
}
