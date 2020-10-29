// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大料二号虎[2;37;0m[2;37;0m", ({"ptwo"}));        
        set("gender", "男性");                
        set("long", "大料二号虎[2;37;0m
它是大料二号的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "phometwo");
        set("owner_name", "大料二号");
        set_temp("owner", "phometwo");
        set_temp("owner_name", "大料二号");
        ::setup();
}
