// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("我的神兽[2;37;0m[2;37;0m", ({"zouyong"}));        
        set("gender", "女性");                
        set("long", "我的神兽[2;37;0m
它是懒虫的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "zou");
        set("owner_name", "懒虫");
        set_temp("owner", "zou");
        set_temp("owner_name", "懒虫");
        ::setup();
}
