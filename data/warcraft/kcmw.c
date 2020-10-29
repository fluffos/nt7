// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m小青蛇[2;37;0m[2;37;0m", ({"qingshe"}));        
        set("gender", "男性");                
        set("long", "小青蛇[2;37;0m
它是康梓三的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kcmw");
        set("owner_name", "康梓三");
        set_temp("owner", "kcmw");
        set_temp("owner_name", "康梓三");
        ::setup();
}
