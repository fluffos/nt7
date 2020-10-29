// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("魔力卡[2;37;0m[2;37;0m", ({"bhi"}));        
        set("gender", "女性");                
        set("long", "八个奶子十张嘴[2;37;0m
它是王七三的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "xixinila");
        set("owner_name", "王七三");
        set_temp("owner", "xixinila");
        set_temp("owner_name", "王七三");
        ::setup();
}
