// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("一群乌鸦[2;37;0m[2;37;0m", ({"xiaojj"}));        
        set("gender", "男性");                
        set("long", "一群乌鸦[2;37;0m
它是洪九儿的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "shsjd");
        set("owner_name", "洪九儿");
        set_temp("owner", "shsjd");
        set_temp("owner_name", "洪九儿");
        ::setup();
}
