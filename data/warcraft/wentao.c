// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小马[2;37;0m[2;37;0m", ({"xiaoma"}));        
        set("gender", "男性");                
        set("long", "小马[2;37;0m
它是咸淡由心的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "wentao");
        set("owner_name", "咸淡由心");
        set_temp("owner", "wentao");
        set_temp("owner_name", "咸淡由心");
        ::setup();
}
