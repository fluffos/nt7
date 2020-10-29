// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m不死姥姥[2;37;0m[2;37;0m", ({"horpse"}));        
        set("gender", "男性");                
        set("long", "$RED$不死姥姥[2;37;0m
它是佩馨的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "ppo");
        set("owner_name", "佩馨");
        set_temp("owner", "ppo");
        set_temp("owner_name", "佩馨");
        ::setup();
}
