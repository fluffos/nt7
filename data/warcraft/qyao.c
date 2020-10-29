// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("肥猫[2;37;0m[2;37;0m", ({"aoq"}));        
        set("gender", "男性");                
        set("long", "老虎[2;37;0m
它是大清药丸的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "qyao");
        set("owner_name", "大清药丸");
        set_temp("owner", "qyao");
        set_temp("owner_name", "大清药丸");
        ::setup();
}
