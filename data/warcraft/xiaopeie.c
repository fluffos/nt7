// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("睡袋[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "睡袋[2;37;0m
它是天蓝蓝的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xiaopeie");
        set("owner_name", "天蓝蓝");
        set_temp("owner", "xiaopeie");
        set_temp("owner_name", "天蓝蓝");
        ::setup();
}
