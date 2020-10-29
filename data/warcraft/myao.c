// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老老老猫[2;37;0m[2;37;0m", ({"aom"}));        
        set("gender", "男性");                
        set("long", "老虎[2;37;0m
它是民国药丸的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "myao");
        set("owner_name", "民国药丸");
        set_temp("owner", "myao");
        set_temp("owner_name", "民国药丸");
        ::setup();
}
