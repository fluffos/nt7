// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("睡袋[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "她叫沈颖红.[2;37;0m
它是凯瑟琳的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "ksl");
        set("owner_name", "凯瑟琳");
        set_temp("owner", "ksl");
        set_temp("owner_name", "凯瑟琳");
        ::setup();
}
