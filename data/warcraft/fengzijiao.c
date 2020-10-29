// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大龙[2;37;0m[2;37;0m", ({"dalong"}));        
        set("gender", "女性");                
        set("long", "大龙[2;37;0m
它是慕容飞机的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "fengzijiao");
        set("owner_name", "慕容飞机");
        set_temp("owner", "fengzijiao");
        set_temp("owner_name", "慕容飞机");
        ::setup();
}
