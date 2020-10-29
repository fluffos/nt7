// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("我的狗[2;37;0m[2;37;0m", ({"mydog"}));        
        set("gender", "女性");                
        set("long", "我的狗[2;37;0m
它是闭月羞花的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "risker");
        set("owner_name", "闭月羞花");
        set_temp("owner", "risker");
        set_temp("owner_name", "闭月羞花");
        ::setup();
}
