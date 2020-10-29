// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m小青[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "小青~~~~~~~~~~~~~~~~~~~[2;37;0m
它是老虎的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "gaj");
        set("owner_name", "老虎");
        set_temp("owner", "gaj");
        set_temp("owner_name", "老虎");
        ::setup();
}
