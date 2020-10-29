// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("天黑[2;37;0m[2;37;0m", ({"heihei"}));        
        set("gender", "男性");                
        set("long", "天黑[2;37;0m
它是天不亮的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lomely");
        set("owner_name", "天不亮");
        set_temp("owner", "lomely");
        set_temp("owner_name", "天不亮");
        ::setup();
}
