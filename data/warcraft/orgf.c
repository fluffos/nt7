// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("你是他[2;37;0m[2;37;0m", ({"hfg"}));        
        set("gender", "女性");                
        set("long", "234[2;37;0m
它是小樱桃的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "orgf");
        set("owner_name", "小樱桃");
        set_temp("owner", "orgf");
        set_temp("owner_name", "小樱桃");
        ::setup();
}
