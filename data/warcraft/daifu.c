// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大飞龙[2;37;0m[2;37;0m", ({"long"}));        
        set("gender", "男性");                
        set("long", "一只器宇轩昂的大飞龙[2;37;0m
它是大夫的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "daifu");
        set("owner_name", "大夫");
        set_temp("owner", "daifu");
        set_temp("owner_name", "大夫");
        ::setup();
}
