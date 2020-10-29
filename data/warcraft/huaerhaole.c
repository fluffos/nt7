// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("好孩子[2;37;0m[2;37;0m", ({"haohaizi"}));        
        set("gender", "男性");                
        set("long", "好孩子[2;37;0m
它是和哦了的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "huaerhaole");
        set("owner_name", "和哦了");
        set_temp("owner", "huaerhaole");
        set_temp("owner_name", "和哦了");
        ::setup();
}
