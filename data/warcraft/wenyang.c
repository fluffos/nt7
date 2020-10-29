// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("张丽华[2;37;0m[2;37;0m", ({"wenlong"}));        
        set("gender", "男性");                
        set("long", "窝藏[2;37;0m
它是文鸯的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wenyang");
        set("owner_name", "文鸯");
        set_temp("owner", "wenyang");
        set_temp("owner_name", "文鸯");
        ::setup();
}
