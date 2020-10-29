// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("木瓜[2;37;0m[2;37;0m", ({"atxi"}));        
        set("gender", "男性");                
        set("long", "木瓜[2;37;0m
它是泥一的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ntba");
        set("owner_name", "泥一");
        set_temp("owner", "ntba");
        set_temp("owner_name", "泥一");
        ::setup();
}
