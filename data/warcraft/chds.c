// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m昊天[2;37;0m[2;37;0m", ({"deep"}));        
        set("gender", "男性");                
        set("long", "哔。。。。[2;37;0m
它是蒙多的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "chds");
        set("owner_name", "蒙多");
        set_temp("owner", "chds");
        set_temp("owner_name", "蒙多");
        ::setup();
}
