// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("哦[2;37;0m[2;37;0m", ({"mhs"}));        
        set("gender", "男性");                
        set("long", "哦[2;37;0m
它是胡铁花的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "chu");
        set("owner_name", "胡铁花");
        set_temp("owner", "chu");
        set_temp("owner_name", "胡铁花");
        ::setup();
}
