// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("非影[2;37;0m[2;37;0m", ({"gogohappy"}));        
        set("gender", "女性");                
        set("long", "无[2;37;0m
它是云淡的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "toho");
        set("owner_name", "云淡");
        set_temp("owner", "toho");
        set_temp("owner_name", "云淡");
        ::setup();
}
