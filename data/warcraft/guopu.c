// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小猫[2;37;0m[2;37;0m", ({"xiaomao"}));        
        set("gender", "女性");                
        set("long", "小猫[2;37;0m
它是真果脯的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "guopu");
        set("owner_name", "真果脯");
        set_temp("owner", "guopu");
        set_temp("owner_name", "真果脯");
        ::setup();
}
