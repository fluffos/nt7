// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("跑你马[2;37;0m[2;37;0m", ({"tant"}));        
        set("gender", "男性");                
        set("long", "囬夺有糘[2;37;0m
它是段覆土的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "tanz");
        set("owner_name", "段覆土");
        set_temp("owner", "tanz");
        set_temp("owner_name", "段覆土");
        ::setup();
}
