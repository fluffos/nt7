// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("一叶扁舟[2;37;0m[2;37;0m", ({"tljbb"}));        
        set("gender", "男性");                
        set("long", "淡淡的山水之间[2;37;0m
它是天龙八部的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "tlbb");
        set("owner_name", "天龙八部");
        set_temp("owner", "tlbb");
        set_temp("owner_name", "天龙八部");
        ::setup();
}
