// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小青[2;37;0m[2;37;0m", ({"dsyd"}));        
        set("gender", "女性");                
        set("long", "小青[2;37;0m
它是为什么的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "dxl");
        set("owner_name", "为什么");
        set_temp("owner", "dxl");
        set_temp("owner_name", "为什么");
        ::setup();
}
