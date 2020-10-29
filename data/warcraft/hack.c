// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大猫[2;37;0m[2;37;0m", ({"lisam"}));        
        set("gender", "男性");                
        set("long", "大猫[2;37;0m
它是骑妹泡猪的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "hack");
        set("owner_name", "骑妹泡猪");
        set_temp("owner", "hack");
        set_temp("owner_name", "骑妹泡猪");
        ::setup();
}
