// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大猫[2;37;0m[2;37;0m", ({"jxuan"}));        
        set("gender", "男性");                
        set("long", "大猫[2;37;0m
它是小轩的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "xuan");
        set("owner_name", "小轩");
        set_temp("owner", "xuan");
        set_temp("owner_name", "小轩");
        ::setup();
}
