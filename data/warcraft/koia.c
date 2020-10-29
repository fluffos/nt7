// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("井冈山[2;37;0m[2;37;0m", ({"yiyayo"}));        
        set("gender", "男性");                
        set("long", "井冈山[2;37;0m
它是米大帮丐的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "koia");
        set("owner_name", "米大帮丐");
        set_temp("owner", "koia");
        set_temp("owner_name", "米大帮丐");
        ::setup();
}
