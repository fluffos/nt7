// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大欧文[2;37;0m[2;37;0m", ({"loih"}));        
        set("gender", "男性");                
        set("long", "大欧文[2;37;0m
它是花猪的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "huazhu");
        set("owner_name", "花猪");
        set_temp("owner", "huazhu");
        set_temp("owner_name", "花猪");
        ::setup();
}
