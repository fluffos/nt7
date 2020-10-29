// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("瘦猫[2;37;0m[2;37;0m", ({"aoh"}));        
        set("gender", "男性");                
        set("long", "老虎[2;37;0m
它是大汉药丸的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "hyao");
        set("owner_name", "大汉药丸");
        set_temp("owner", "hyao");
        set_temp("owner_name", "大汉药丸");
        ::setup();
}
