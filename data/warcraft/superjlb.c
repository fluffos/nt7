// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("魔幻兽[2;37;0m[2;37;0m", ({"roman"}));        
        set("gender", "男性");                
        set("long", "ginish[2;37;0m
它是午夜失眠的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "superjlb");
        set("owner_name", "午夜失眠");
        set_temp("owner", "superjlb");
        set_temp("owner_name", "午夜失眠");
        ::setup();
}
