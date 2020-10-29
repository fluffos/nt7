// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小龙[2;37;0m[2;37;0m", ({"xiaoq"}));        
        set("gender", "女性");                
        set("long", "小龙[2;37;0m
它是看丫的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kkkya");
        set("owner_name", "看丫");
        set_temp("owner", "kkkya");
        set_temp("owner_name", "看丫");
        ::setup();
}
