// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("避水金晶兽[2;37;0m[2;37;0m", ({"mos"}));        
        set("gender", "女性");                
        set("long", "一头避水金晶兽[2;37;0m
它是周日月的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "butongb");
        set("owner_name", "周日月");
        set_temp("owner", "butongb");
        set_temp("owner_name", "周日月");
        ::setup();
}
