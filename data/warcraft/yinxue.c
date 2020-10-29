// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m沁雪[2;37;0m[2;37;0m", ({"icer"}));        
        set("gender", "女性");                
        set("long", "一团雪白的小绒球，滚来滚去[2;37;0m
它是吟雪的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "yinxue");
        set("owner_name", "吟雪");
        set_temp("owner", "yinxue");
        set_temp("owner_name", "吟雪");
        ::setup();
}
