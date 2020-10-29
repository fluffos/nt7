// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("好烦[2;37;0m[2;37;0m", ({"haofan"}));        
        set("gender", "男性");                
        set("long", "垃圾国足[2;37;0m
它是国足烦的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "gzfan");
        set("owner_name", "国足烦");
        set_temp("owner", "gzfan");
        set_temp("owner_name", "国足烦");
        ::setup();
}
