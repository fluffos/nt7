// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("二大爷[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "二大爷[2;37;0m
它是红鹿的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "remn");
        set("owner_name", "红鹿");
        set_temp("owner", "remn");
        set_temp("owner_name", "红鹿");
        ::setup();
}
