// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("跳蚤[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "跳蚤[2;37;0m
它是绿臭虫的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "bugb");
        set("owner_name", "绿臭虫");
        set_temp("owner", "bugb");
        set_temp("owner_name", "绿臭虫");
        ::setup();
}
