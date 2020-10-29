// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("云朵[2;37;0m[2;37;0m", ({"horse"}));        
        set("gender", "男性");                
        set("long", "unset no_accept[2;37;0m
它是莎琳娜的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "ssmile");
        set("owner_name", "莎琳娜");
        set_temp("owner", "ssmile");
        set_temp("owner_name", "莎琳娜");
        ::setup();
}
