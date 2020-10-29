// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("虎豹[2;37;0m[2;37;0m", ({"huhu"}));        
        set("gender", "男性");                
        set("long", "凶猛[2;37;0m
它是胡疯神的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "hmjli");
        set("owner_name", "胡疯神");
        set_temp("owner", "hmjli");
        set_temp("owner_name", "胡疯神");
        ::setup();
}
