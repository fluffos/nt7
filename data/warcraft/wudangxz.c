// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"wudanglong"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是张乌当的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wudangxz");
        set("owner_name", "张乌当");
        set_temp("owner", "wudangxz");
        set_temp("owner_name", "张乌当");
        ::setup();
}
