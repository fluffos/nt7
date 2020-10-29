// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小红米[2;37;0m[2;37;0m", ({"xmi"}));        
        set("gender", "男性");                
        set("long", "小红米[2;37;0m
它是白米饭的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "mifan");
        set("owner_name", "白米饭");
        set_temp("owner", "mifan");
        set_temp("owner_name", "白米饭");
        ::setup();
}
