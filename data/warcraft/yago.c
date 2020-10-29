// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("波多野结衣[2;37;0m[2;37;0m", ({"boduo"}));        
        set("gender", "女性");                
        set("long", "天使的脸蛋魔鬼的身材[2;37;0m
它是南宫城的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "yago");
        set("owner_name", "南宫城");
        set_temp("owner", "yago");
        set_temp("owner_name", "南宫城");
        ::setup();
}
