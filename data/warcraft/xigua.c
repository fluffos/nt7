// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青水[2;37;0m[2;37;0m", ({"qingshui"}));        
        set("gender", "女性");                
        set("long", "青清白白的水[2;37;0m
它是西瓜的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xigua");
        set("owner_name", "西瓜");
        set_temp("owner", "xigua");
        set_temp("owner_name", "西瓜");
        ::setup();
}
