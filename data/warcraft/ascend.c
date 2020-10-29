// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("风翼天翔[2;37;0m[2;37;0m", ({"apollo"}));        
        set("gender", "女性");                
        set("long", "小飞鸟[2;37;0m
它是艾欧里亚的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ascend");
        set("owner_name", "艾欧里亚");
        set_temp("owner", "ascend");
        set_temp("owner_name", "艾欧里亚");
        ::setup();
}
