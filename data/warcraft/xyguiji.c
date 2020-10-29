// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大海龟[2;37;0m[2;37;0m", ({"baoma"}));        
        set("gender", "男性");                
        set("long", "大海龟[2;37;0m
它是没商圣龙的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "xyguiji");
        set("owner_name", "没商圣龙");
        set_temp("owner", "xyguiji");
        set_temp("owner_name", "没商圣龙");
        ::setup();
}
