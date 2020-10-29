// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白狐[2;37;0m[2;37;0m", ({"baihu"}));        
        set("gender", "男性");                
        set("long", "白[2;37;0m
它是风姿的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "fengzi");
        set("owner_name", "风姿");
        set_temp("owner", "fengzi");
        set_temp("owner_name", "风姿");
        ::setup();
}
