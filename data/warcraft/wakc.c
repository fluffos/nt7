// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小龙[2;37;0m[2;37;0m", ({"xiaoq"}));        
        set("gender", "女性");                
        set("long", "小龙[2;37;0m
它是空虚的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wakc");
        set("owner_name", "空虚");
        set_temp("owner", "wakc");
        set_temp("owner_name", "空虚");
        ::setup();
}
