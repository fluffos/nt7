// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大料一号兽[2;37;0m[2;37;0m", ({"pphomeone"}));        
        set("gender", "女性");                
        set("long", "大料一号兽[2;37;0m
它是大料一号的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "phomeone");
        set("owner_name", "大料一号");
        set_temp("owner", "phomeone");
        set_temp("owner_name", "大料一号");
        ::setup();
}
