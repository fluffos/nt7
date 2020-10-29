// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大白[2;37;0m[2;37;0m", ({"baihu"}));        
        set("gender", "女性");                
        set("long", "大白[2;37;0m
它是梦梦帝的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "aiwr");
        set("owner_name", "梦梦帝");
        set_temp("owner", "aiwr");
        set_temp("owner_name", "梦梦帝");
        ::setup();
}
