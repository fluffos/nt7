// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大众[2;37;0m[2;37;0m", ({"daibu"}));        
        set("gender", "女性");                
        set("long", "好车[2;37;0m
它是难得糊涂的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kokoya");
        set("owner_name", "难得糊涂");
        set_temp("owner", "kokoya");
        set_temp("owner_name", "难得糊涂");
        ::setup();
}
