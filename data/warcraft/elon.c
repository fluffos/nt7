// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("霸王龙[2;37;0m[2;37;0m", ({"dargon"}));        
        set("gender", "男性");                
        set("long", "凶猛的龙[2;37;0m
它是寒雨凉的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "elon");
        set("owner_name", "寒雨凉");
        set_temp("owner", "elon");
        set_temp("owner_name", "寒雨凉");
        ::setup();
}
