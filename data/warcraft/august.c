// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m浴火重生[2;37;0m[2;37;0m", ({"qwe"}));        
        set("gender", "男性");                
        set("long", "FUCK[2;37;0m
它是小慕的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "august");
        set("owner_name", "小慕");
        set_temp("owner", "august");
        set_temp("owner_name", "小慕");
        ::setup();
}
