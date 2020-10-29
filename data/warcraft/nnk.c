// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小眼[2;37;0m[2;37;0m", ({"myzuoqi"}));        
        set("gender", "女性");                
        set("long", "小眼[2;37;0m
它是埃莉脑梗的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "nnk");
        set("owner_name", "埃莉脑梗");
        set_temp("owner", "nnk");
        set_temp("owner_name", "埃莉脑梗");
        ::setup();
}
