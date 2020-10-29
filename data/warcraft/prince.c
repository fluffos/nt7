// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m金甲[1;31m霸王龙[2;37;0m[2;37;0m", ({"berserk"}));        
        set("gender", "男性");                
        set("long", "暴力王子的坐骑。一头全身金甲鳞片的巨大霸王龙！[2;37;0m
它是暴力王子的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "prince");
        set("owner_name", "暴力王子");
        set_temp("owner", "prince");
        set_temp("owner_name", "暴力王子");
        ::setup();
}
