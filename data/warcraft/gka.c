// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小青龙[2;37;0m[2;37;0m", ({"xql"}));        
        set("gender", "男性");                
        set("long", "我是一条小青龙。[2;37;0m
它是欧阳一的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "gka");
        set("owner_name", "欧阳一");
        set_temp("owner", "gka");
        set_temp("owner_name", "欧阳一");
        ::setup();
}
