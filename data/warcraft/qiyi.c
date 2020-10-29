// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("猫[2;37;0m[2;37;0m", ({"mao"}));        
        set("gender", "女性");                
        set("long", "一只小猫[2;37;0m
它是绮伊的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "qiyi");
        set("owner_name", "绮伊");
        set_temp("owner", "qiyi");
        set_temp("owner_name", "绮伊");
        ::setup();
}
