// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("玫瑰[2;37;0m[2;37;0m", ({"roes"}));        
        set("gender", "男性");                
        set("long", "花[2;37;0m
它是风来鸭的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "hjdn");
        set("owner_name", "风来鸭");
        set_temp("owner", "hjdn");
        set_temp("owner_name", "风来鸭");
        ::setup();
}
