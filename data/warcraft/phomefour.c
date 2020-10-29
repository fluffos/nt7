// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大料四号兽[2;37;0m[2;37;0m", ({"pphomefour"}));        
        set("gender", "女性");                
        set("long", "大料四号兽[2;37;0m
它是大料四号的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "phomefour");
        set("owner_name", "大料四号");
        set_temp("owner", "phomefour");
        set_temp("owner_name", "大料四号");
        ::setup();
}
