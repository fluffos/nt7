// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大鸟[2;37;0m[2;37;0m", ({"hhh"}));        
        set("gender", "男性");                
        set("long", "11[2;37;0m
它是弗洛雷斯的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "houston");
        set("owner_name", "弗洛雷斯");
        set_temp("owner", "houston");
        set_temp("owner_name", "弗洛雷斯");
        ::setup();
}
